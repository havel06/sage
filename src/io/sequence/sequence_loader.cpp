#include "sequence_loader.hpp"
#include "character_profile.hpp"
#include "combat/battle_desc.hpp"
#include "graphics/ui/layout.hpp"
#include "io/gui_loader.hpp"
#include "io/resource/texture_manager.hpp"
#include "sequence/event_parameter.hpp"
#include "utils/move.hpp"
#include "sequence/conditions/has_item.hpp"
#include "sequence/conditions/not.hpp"
#include "sequence/conditions/is_in_combat.hpp"
#include "sequence/condition_factories/not.hpp"
#include "sequence/condition_factories/has_item.hpp"
#include "sequence/condition_factories/is_in_combat.hpp"
#include "sequence/sequence.hpp"
#include "sequence/event_factory.hpp"
#include "utils/direction.hpp"
#include "utils/file.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "../json_types.hpp"
#include "../resource/resource_system.hpp"

Sequence_Loader::Sequence_Loader(const String& resource_root_path, Resource_System& res_system, Game_Facade& facade, GUI_Loader& gui_loader) :
	m_event_parameter_parser(*this, res_system.texture_manager),
	m_event_parser{m_event_parameter_parser, res_system, gui_loader, facade},
	m_facade{facade},
	m_resource_system{res_system},
	m_gui_loader{gui_loader}
{
	m_resource_root_path = resource_root_path;
}

Sequence Sequence_Loader::load(const String& filename)
{
	SG_DEBUG("Parsing sequence %s", filename.data());
	const JSON::Object json = JSON::Object::from_file(filename.data());
	const JSON::Object_View view = json.get_view();

	if (view.has("from_template")) {
		// Load sequence from template
		JSON::Object_View template_spec = view["from_template"].as_object();
		String template_filename = m_resource_root_path;
		template_filename.append('/');
		template_filename.append(template_spec["template"].as_string(""));
		JSON::Object_View params = template_spec["parameters"].as_object();

		JSON::Object template_json = JSON::Object::from_file(template_filename.data());

		SG_DEBUG("Parsing sequence template %s", template_filename.data());
		return load_templated_sequence(template_json.get_view(), params);

	} else {
		// Load normal, non-templated sequence
		JSON::Object empty_parameters;
		return load_templated_sequence(view, empty_parameters.get_view());
	}
}

Sequence Sequence_Loader::load_templated_sequence(
		const JSON::Object_View& template_json,
		const JSON::Object_View& parameters)
{
	Sequence sequence;

	if (template_json.has("repeatable")) {
		sequence.repeatable = template_json["repeatable"].as_bool(false);
	}

	// Events
	template_json["events"].as_array().for_each([&](const JSON::Value_View& event_json) {
		Event_Ptr event = m_event_parser.parse_event(event_json.as_object(), parameters);

		if (event)
			sequence.add_event(move(event));
	});

	// Condition
	if (template_json.has("condition")) {
		sequence.set_condition(parse_condition(template_json["condition"].as_object(), parameters));
	}

	return sequence;
}



void Sequence_Loader::parse_condition_parameters(Condition_Factory& factory,
		const JSON::Object_View& parameters,
		const JSON::Object_View& template_parameters)
{
	factory.for_each_parameter([&](const String& name, Event_Parameter& parameter){
		if (!parameters.has(name.data())) {
			SG_ERROR("Missing event parameter \"%s\"", name.data());
			assert(false);
		}

		const JSON::Value_View& unresolved_value = parameters[name.data()];
		m_event_parameter_parser.parse(parameter, unresolved_value, template_parameters);
	});
}

Condition_Ptr Sequence_Loader::parse_condition(
		const JSON::Object_View& json,
		const JSON::Object_View& template_params)
{
	const String type = json["type"].as_string("");
	if (type.empty()) {
		SG_ERROR("Missing condition type.");
		return nullptr;
	}

	const JSON::Object_View params = json["parameters"].as_object();
	Own_Ptr<Condition_Factory> factory = get_factory_for_condition_type(type);

	if (factory) {
		parse_condition_parameters(*factory, params, template_params);
		return factory->make_condition(m_facade);
	} else {
		return nullptr;
	}
}

Own_Ptr<Condition_Factory> Sequence_Loader::get_factory_for_condition_type(const String& type)
{
	if (type == "not") {
		return make_own_ptr<Condition_Factories::Not>();
	} else if (type == "has_item") {
		return make_own_ptr<Condition_Factories::Has_Item>();
	} else if (type == "is_in_combat") {
		return make_own_ptr<Condition_Factories::Is_In_Combat>();
	} else {
		SG_ERROR("Invalid event type \"%s\"", type.data());
		return nullptr;
	}
}

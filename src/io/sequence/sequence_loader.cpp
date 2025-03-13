#include "sequence_loader.hpp"
#include "character_profile.hpp"
#include "combat/battle_desc.hpp"
#include "io/gui_loader.hpp"
#include "io/parameter_parser.hpp"
#include "io/resource/texture_manager.hpp"
#include "sequence/condition.hpp"
#include "utils/move.hpp"
#include "sequence/sequence.hpp"
#include "sequence/event_factory.hpp"
#include "utils/direction.hpp"
#include "utils/file.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "../json_types.hpp"
#include "../resource/resource_system.hpp"

Sequence_Loader::Sequence_Loader(
	const String& resource_root_path,
	Resource_System& res_system,
	Parameter_Parser& param_parser,
	Condition_Parser& condition_parser,
	Game_Facade& facade
) :
	m_parameter_parser{param_parser},
	m_condition_parser{condition_parser},
	m_event_parser{m_parameter_parser, res_system, facade}
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
		parse_event(sequence, event_json.as_object(), parameters);
	});

	// Condition
	if (template_json.has("condition")) {
		JSON::Object_View condition_json = template_json["condition"].as_object();
		Condition_Ptr condition = m_condition_parser.parse_condition(condition_json, parameters);

		if (condition)
			sequence.set_condition(move(condition));
	}

	return sequence;
}

void Sequence_Loader::parse_event(
	Sequence& sequence,
	const JSON::Object_View& json,
	const JSON::Object_View& template_params)
{
	if (json.has("from_template")) {
		// Use sequence event template
		JSON::Object_View template_spec = json["from_template"].as_object();
		String template_filename = m_resource_root_path;
		template_filename.append('/');
		template_filename.append(template_spec["template"].as_string(""));
		JSON::Object_View params = template_spec["parameters"].as_object();

		JSON::Object template_json = JSON::Object::from_file(template_filename.data());

		SG_DEBUG("Parsing event group template %s", template_filename.data());

		JSON::Array_View events_json = template_json.get_view().get("events").as_array();
		events_json.for_each([&](const JSON::Value_View& event_json){
			parse_event(sequence, event_json.as_object(), params);
		});
	} else {
		// Parse event normally
		Event_Ptr event = m_event_parser.parse_event(json, template_params);
		if (event)
			sequence.add_event(move(event));
	}
}

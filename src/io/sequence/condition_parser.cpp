#include "condition_parser.hpp"
#include "sequence/condition_factory.hpp"
#include "utils/json.hpp"
#include "utils/own_ptr.hpp"
#include "utils/log.hpp"
#include "event_parameter_parser.hpp"
#include "sequence/condition_factories/not.hpp"
#include "sequence/condition_factories/has_item.hpp"
#include "sequence/condition_factories/is_in_combat.hpp"

Condition_Parser::Condition_Parser(Event_Parameter_Parser& parameter_parser, Game_Facade& facade) :
	m_event_parameter_parser{parameter_parser},
	m_facade{facade}
{
}


void Condition_Parser::parse_condition_parameters(Condition_Factory& factory,
		const JSON::Object_View& parameters,
		const JSON::Object_View& template_parameters)
{
	factory.for_each_parameter([&](const String& name, Event_Parameter& parameter){
		if (!parameters.has(name.data())) {
			SG_ERROR("Missing condition parameter \"%s\"", name.data());
			assert(false);
		}

		const JSON::Value_View& unresolved_value = parameters[name.data()];
		m_event_parameter_parser.parse(parameter, unresolved_value, template_parameters);
	});
}

Own_Ptr<Condition> Condition_Parser::parse_condition(
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

Own_Ptr<Condition_Factory> Condition_Parser::get_factory_for_condition_type(const String& type)
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

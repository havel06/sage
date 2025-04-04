#include "condition_parser.hpp"
#include "sequence/condition_factory.hpp"
#include "utils/json.hpp"
#include "utils/own_ptr.hpp"
#include "utils/log.hpp"
#include "../parameter_parser.hpp"
#include "sequence/condition_factories/and.hpp"
#include "sequence/condition_factories/not.hpp"
#include "sequence/condition_factories/has_item.hpp"
#include "sequence/condition_factories/is_in_combat.hpp"
#include "sequence/condition_factories/player_is_looking.hpp"
#include "sequence/condition_factories/is_passable.hpp"

Condition_Parser::Condition_Parser(Parameter_Parser& parameter_parser, Game_Facade& facade) :
	m_parameter_parser{parameter_parser},
	m_facade{facade}
{
}


void Condition_Parser::parse_condition_parameters(Condition_Factory& factory,
		const JSON::Object_View& parameters,
		const JSON::Object_View& template_parameters)
{
	factory.for_each_parameter([&](const String& name, Parameter& parameter){
		if (!parameters.has(name.data())) {
			SG_ERROR("Missing condition parameter \"%s\"", name.data());
			assert(false);
		}

		const JSON::Value_View& unresolved_value = parameters[name.data()];
		m_parameter_parser.parse(parameter, unresolved_value, template_parameters);
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
	} else if (type == "and") {
		return make_own_ptr<Condition_Factories::And>();
	} else if (type == "has_item") {
		return make_own_ptr<Condition_Factories::Has_Item>();
	} else if (type == "is_in_combat") {
		return make_own_ptr<Condition_Factories::Is_In_Combat>();
	} else if (type == "player_is_looking") {
		return make_own_ptr<Condition_Factories::Player_Is_Looking>();
	} else if (type == "is_passable") {
		return make_own_ptr<Condition_Factories::Is_Passable>();
	} else {
		SG_ERROR("Invalid condition type \"%s\"", type.data());
		return nullptr;
	}
}

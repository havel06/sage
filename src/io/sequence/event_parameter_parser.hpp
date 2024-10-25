#pragma once


// fwd
class Condition_Parser;
class Texture_Manager;
class Event_Parameter;
struct Battle_Unit_Placement;
struct Battle_Units_Layout;
namespace JSON {
	class Object_View;
	class Value_View;
}


class Event_Parameter_Parser
{
public:
	Event_Parameter_Parser(Condition_Parser&, Texture_Manager&);
	void parse(Event_Parameter& parameter, const JSON::Value_View& unresolved_value, const JSON::Object_View& template_parameters);
private:
	static Battle_Units_Layout parse_battle_units_layout(const JSON::Object_View& json);
	static Battle_Unit_Placement parse_battle_unit(const JSON::Object_View& json);

	Condition_Parser& m_condition_parser;
	Texture_Manager& m_texture_manager;

	class Visitor; // fwd
};

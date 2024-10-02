#pragma once

// fwd
class Condition;
template<typename T>
class Own_Ptr;
class Condition_Factory;
class String;
class Game_Facade;
class Event_Parameter_Parser;
namespace JSON {
	class Object_View;
}

class Condition_Parser
{
public:
	Condition_Parser(Event_Parameter_Parser&, Game_Facade&);
	Own_Ptr<Condition> parse_condition(const JSON::Object_View&, const JSON::Object_View& template_parameters);
private:
	Own_Ptr<Condition_Factory> get_factory_for_condition_type(const String& type);
	void parse_condition_parameters(Condition_Factory& factory,
			const JSON::Object_View& event_parameters,
			const JSON::Object_View& template_parameters);

	Event_Parameter_Parser& m_event_parameter_parser;
	Game_Facade& m_facade;
};

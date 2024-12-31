#pragma once

// fwd
class Event;
template<typename T>
class Own_Ptr;
class Event_Factory;
class String;
class Game_Facade;
class Resource_System;
class GUI_Loader;
class Event_Parameter_Parser;
namespace JSON {
	class Object_View;
}

class Event_Parser
{
public:
	Event_Parser(Event_Parameter_Parser&, Resource_System&, Game_Facade&);
	Own_Ptr<Event> parse_event(const JSON::Object_View&, const JSON::Object_View& template_parameters);
private:
	Own_Ptr<Event_Factory> get_factory_for_event_type(const String& type);
	void parse_event_parameters(Event_Factory& factory,
			const JSON::Object_View& event_parameters,
			const JSON::Object_View& template_parameters);

	Event_Parameter_Parser& m_event_parameter_parser;
	Game_Facade& m_facade;
	Resource_System& m_resource_system;
};

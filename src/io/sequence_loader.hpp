#pragma once

#include "utils/string.hpp"
#include "sequence/sequence.hpp"

// fwd
class Resource_System;
class Game_Facade;
class GUI_Loader;
class Event_Factory;
namespace JSON {
	class Object_View;
	class Value_View;
}

class Sequence_Loader
{
public:
	Sequence_Loader(const String& resource_root_path, Resource_System&, Game_Facade&, GUI_Loader&);
	Sequence load(const String& filename);
private:
	Sequence load_templated_sequence(const String& final_filename, const JSON::Object_View& template_json, const JSON::Object_View& parameters);

	// FIXME - move event related things to separate class
	Event_Ptr parse_event(const JSON::Object_View&, const JSON::Object_View& parameters);
	Own_Ptr<Event_Factory> get_factory_for_event_type(const String& type);
	void parse_event_parameters(Event_Factory& factory,
			const JSON::Object_View& event_parameters,
			const JSON::Object_View& template_parameters);

	Condition_Ptr parse_condition(const JSON::Object_View&);

	// Returns either the value of val, or value of template parameter referred to by val
	JSON::Value_View resolve_value(const JSON::Value_View& val, const JSON::Object_View& template_parameters);

	String m_resource_root_path;
	Game_Facade& m_facade;
	Resource_System& m_resource_system;
	GUI_Loader& m_gui_loader;
};

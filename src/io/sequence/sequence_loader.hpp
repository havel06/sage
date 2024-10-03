#pragma once

#include "utils/string.hpp"
#include "sequence/sequence.hpp"
#include "event_parameter_parser.hpp"
#include "event_parser.hpp"
#include "condition_parser.hpp"

// fwd
class Resource_System;
class Game_Facade;
class GUI_Loader;
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
	Own_Ptr<Event> parse_event(const JSON::Object_View& json, const JSON::Object_View& template_params);
	Sequence load_templated_sequence(const JSON::Object_View& template_json, const JSON::Object_View& parameters);

	String m_resource_root_path;
	Event_Parameter_Parser m_event_parameter_parser;
	Event_Parser m_event_parser; // FIXME - DI
	Condition_Parser m_condition_parser;
	Game_Facade& m_facade;
	Resource_System& m_resource_system;
	GUI_Loader& m_gui_loader;
};

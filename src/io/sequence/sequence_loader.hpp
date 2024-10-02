#pragma once

#include "utils/string.hpp"
#include "sequence/sequence.hpp"
#include "event_parameter_parser.hpp"
#include "event_parser.hpp"

// fwd
class Resource_System;
class Game_Facade;
class GUI_Loader;
class Event_Factory;
class Condition_Factory;
class Event_Parameter;
namespace JSON {
	class Object_View;
	class Value_View;
}

class Sequence_Loader
{
public:
	Sequence_Loader(const String& resource_root_path, Resource_System&, Game_Facade&, GUI_Loader&);
	Sequence load(const String& filename);

	// FIXME - move to separate class
	Condition_Ptr parse_condition(const JSON::Object_View&, const JSON::Object_View& template_parameters);
private:
	Sequence load_templated_sequence(const JSON::Object_View& template_json, const JSON::Object_View& parameters);

	// FIXME - move condition related things to separate class
	Own_Ptr<Condition_Factory> get_factory_for_condition_type(const String& type);
	void parse_condition_parameters(Condition_Factory& factory,
			const JSON::Object_View& event_parameters,
			const JSON::Object_View& template_parameters);

	String m_resource_root_path;
	Event_Parameter_Parser m_event_parameter_parser;
	Event_Parser m_event_parser; // FIXME - DI
	Game_Facade& m_facade;
	Resource_System& m_resource_system;
	GUI_Loader& m_gui_loader;
};

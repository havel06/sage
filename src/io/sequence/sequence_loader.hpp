#pragma once

#include "utils/string.hpp"
#include "sequence/sequence.hpp"
#include "../parameter_parser.hpp"
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
	Sequence_Loader(const String& resource_root_path, Resource_System&, Game_Facade&);
	Sequence load(const String& filename);

private:
	void parse_event(Sequence& sequence, const JSON::Object_View& json, const JSON::Object_View& template_params);
	Sequence load_templated_sequence(const JSON::Object_View& template_json, const JSON::Object_View& parameters);

	String m_resource_root_path;
	Parameter_Parser m_parameter_parser;
	Event_Parser m_event_parser; // FIXME - DI???
	Condition_Parser m_condition_parser;
};

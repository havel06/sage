#pragma once

#include "utils/string.hpp"
#include "sequence/sequence.hpp"

// fwd
class Resource_System;
class Game_Facade;
namespace JSON {
	class Object_View;
}

class Sequence_Loader
{
public:
	Sequence_Loader(Resource_System&, Game_Facade&);
	Sequence load(const String& filename);
private:
	Event_Ptr parse_event(const JSON::Object_View&);
	Condition_Ptr parse_condition(const JSON::Object_View&);

	Game_Facade& m_facade;
	Resource_System& m_resource_system;
};

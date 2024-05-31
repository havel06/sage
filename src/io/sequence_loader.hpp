#pragma once

#include "utils/string.hpp"
#include "sequence/sequence.hpp"

// fwd
struct cJSON;
class Resource_System;
class Game_Facade;

class Sequence_Loader
{
public:
	Sequence_Loader(Resource_System&, Game_Facade&);
	Sequence load(const String& filename);
private:
	Event_Ptr parse_event(const cJSON*);
	Condition_Ptr parse_condition(const cJSON*);

	Game_Facade& m_facade;
	Resource_System& m_resource_system;
};

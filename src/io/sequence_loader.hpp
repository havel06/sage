#pragma once

#include "utils/string.hpp"
#include "sequence/sequence.hpp"

// fwd
struct cJSON;
class Resource_Manager;
class Game_Facade;

class Sequence_Loader
{
public:
	Sequence_Loader(Resource_Manager&, Game_Facade&);
	Sequence load(const String& filename);
private:
	Event_Ptr parse_event(const cJSON*);

	Game_Facade& m_facade;
	Resource_Manager& m_resource_manager;
};

#pragma once

#include "utils/string.hpp"
#include "sequence/sequence.hpp"

// fwd
struct cJSON;
class Resource_Manager;

class Sequence_Loader
{
public:
	Sequence_Loader(Resource_Manager&);
	Sequence load(const String& filename);
private:
	Event_Ptr parse_event(const cJSON*);

	Resource_Manager& m_resource_manager;
};

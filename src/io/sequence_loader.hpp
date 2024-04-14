#pragma once

#include "utils/string.hpp"
#include "sequence/sequence.hpp"

// fwd
struct cJSON;

class Sequence_Loader
{
public:
	Sequence load(const String& filename);
private:
	Event_Ptr parse_event(const cJSON*);
};

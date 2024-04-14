#pragma once

#include "utils/string.hpp"
#include "sequence/sequence.hpp"

class Sequence_Loader
{
public:
	Sequence load(const String& filename);
};

#pragma once

#include "sequence/sequence.hpp"
#include "utils/array.hpp"

// FIXME - use this or delete

// NOTE - does not own memory
class Sequence_Manager
{
public:
	void add(Sequence*);
	void update(float time_delta);
private:
	Array<Sequence*> m_sequences;
};

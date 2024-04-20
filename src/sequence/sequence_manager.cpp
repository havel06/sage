#include "sequence_manager.hpp"
#include "io/resource_manager.hpp"

void Sequence_Manager::add(Sequence* seq)
{
	if (!m_sequences.contains(seq))
		m_sequences.push_back(seq);
}

void Sequence_Manager::update(float time_delta)
{
	for (int i = 0; i < m_sequences.size(); i++) {
		m_sequences[i]->update(time_delta);
	}
}

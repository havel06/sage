#include "activate_sequence.hpp"
#include "../sequence.hpp"
#include "utils/log.hpp"

namespace Events
{

Activate_Sequence::Activate_Sequence(Game_Facade& facade, Resource_Handle<Sequence> sequence) :
	Event{facade},
	m_sequence{sequence}
{
}

void Activate_Sequence::update(float)
{
	if (!m_activated) {
		m_sequence.get().try_activate();
		m_activated = true;
	}
}

bool Activate_Sequence::is_finished() const
{
	return m_activated;
}

void Activate_Sequence::reset()
{
	m_activated = false;
}

}

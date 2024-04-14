#include "sequence.hpp"

void Sequence::add_event(Event_Ptr&& event)
{
	m_events.push_back((Event_Ptr&&)event);
}

void Sequence::update(Game_Facade& game_facade, float time_delta)
{
	if (!m_active || m_finished)
		return;

	// Run current event
	while (true) {
		m_events[m_current_event]->update(game_facade, time_delta);

		if (m_events[m_current_event]->is_finished()) {
			m_current_event++;
			continue;
		} else {
			break;
		}
	}

	// Check if sequence has ended
	if (m_current_event >= m_events.size()) {
		m_finished = true;
	}
}

void Sequence::activate()
{
	m_active = true;
}

#include "sequence.hpp"
#include "utils/log.hpp"

void Sequence::add_event(Event_Ptr&& event)
{
	m_events.push_back((Event_Ptr&&)event);
}

void Sequence::update(Game_Facade& game_facade, float time_delta)
{
	if (!m_active || m_finished || m_events.empty())
		return;

	for (int i = 0; i < m_events.size(); i++) {
		// Update event
		m_events[i]->update(game_facade, time_delta);

		if (m_events[i]->is_finished(game_facade))
			continue;

		if (!m_events[i]->asynchronous)
			break;
	}

	// Check if all events are finished
	bool all_finished = true;
	for (int i = 0; i < m_events[i]; i++) {
		if (!m_events[i]->is_finished(game_facade))
			all_finished = false;
	}

	if (all_finished)
		end_or_reset();
}

void Sequence::end_or_reset()
{
	m_active = false;

	if (!repeatable) {
		m_finished = true;
	} else {
		// Reset events
		for (int i = 0; i < m_events.size(); i++)
			m_events[i]->reset();
	}
}

void Sequence::activate()
{
	m_active = true;
}

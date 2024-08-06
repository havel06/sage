#include "sequence.hpp"
#include "game/game_facade.hpp"
#include "utils/log.hpp"

Sequence::Sequence(const String& path)
{
	m_path = path;
}

void Sequence::add_event(Event_Ptr&& event)
{
	m_events.push_back((Event_Ptr&&)event);
}

void Sequence::set_condition(Condition_Ptr&& condition)
{
	m_condition = (Condition_Ptr&&)condition;
}

void Sequence::set_current_event(int index)
{
	if (index > m_events.size()) {
		end_or_reset();
	} else {
		// We don't want an unfinished sequence marked as finished!
		m_finished = false;
	}

	m_current_event = index;
}

void Sequence::update(float time_delta)
{
	if (!m_active || m_finished || m_events.empty())
		return;

	for (int i = m_current_event; i < m_events.size(); i++) {
		// Update event
		m_events[i]->update(time_delta);

		if (m_events[i]->is_finished()) {
			if (i == m_current_event)
				m_current_event++;

			continue;
		}

		if (!m_events[i]->asynchronous)
			break;
	}

	// Check if all events are finished
	if (m_current_event >= m_events.size())
		end_or_reset();
}

void Sequence::end_or_reset()
{
	if (!repeatable) {
		// End
		m_active = false;
		m_finished = true;
	} else {
		reset();
	}
}

void Sequence::reset()
{
	// Reset events
	for (int i = 0; i < m_events.size(); i++)
		m_events[i]->reset();

	m_current_event = 0;
	m_active = false;
	m_finished = false;
}

void Sequence::try_activate()
{
	if (m_active || m_finished)
		return;

	if (m_condition && !m_condition->is_satisfied())
		return;

	m_active = true;
}

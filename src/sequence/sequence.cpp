#include "sequence.hpp"
#include "game_facade.hpp"
#include "utils/log.hpp"

void Sequence::add_event(Event_Ptr&& event)
{
	m_events.push_back((Event_Ptr&&)event);
}

void Sequence::set_condition(Condition_Ptr&& condition)
{
	m_condition = (Condition_Ptr&&)condition;
}

void Sequence::update(float time_delta)
{
	if (!m_active || m_finished || m_events.empty())
		return;

	for (int i = 0; i < m_events.size(); i++) {
		// Update event
		m_events[i]->update(time_delta);

		if (m_events[i]->is_finished())
			continue;

		if (!m_events[i]->asynchronous)
			break;
	}

	// Check if all events are finished
	bool all_finished = true;
	for (int i = 0; i < m_events.size(); i++) {
		if (!m_events[i]->is_finished())
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

void Sequence::try_activate()
{
	if (m_condition && !m_condition->is_satisfied())
		return;

	m_active = true;
}

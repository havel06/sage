#pragma once

#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "event.hpp"
#include "condition.hpp"
#include "utils/string.hpp"

using Event_Ptr = Own_Ptr<Event>;

class Sequence
{
public:
	bool repeatable = false;

	void set_condition(Condition_Ptr&&);
	void add_event(Event_Ptr&&);
	void set_current_event(int index);

	void update(float time_delta);
	void try_activate();
	void reset();

	bool is_active() const { return m_active; }
	// Only makes sense to use for non-repeatable sequences
	bool has_finished() const { return m_finished; }
	int get_current_event_index() const { return m_current_event; }
private:
	void end_or_reset();

	bool m_active = false;
	bool m_finished = false;
	int m_current_event = 0;
	Condition_Ptr m_condition;
	Array<Event_Ptr> m_events;
};

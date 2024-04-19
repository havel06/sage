#pragma once

#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "event.hpp"
#include "condition.hpp"

using Event_Ptr = Own_Ptr<Event>;

class Sequence
{
public:
	bool repeatable = false;

	void set_condition(Condition_Ptr&&);
	void add_event(Event_Ptr&&);
	void update(float time_delta);
	void try_activate();
private:
	void end_or_reset();

	bool m_active = false;
	bool m_finished = false;
	Condition_Ptr m_condition;
	Array<Event_Ptr> m_events;
};

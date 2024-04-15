#pragma once

#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "event.hpp"

using Event_Ptr = Own_Ptr<Event>;

class Sequence
{
public:
	void add_event(Event_Ptr&&);
	void update(Game_Facade&, float time_delta);
	void activate();
private:
	bool m_active = false;
	bool m_finished = false;
	int m_current_event = 0;
	Array<Event_Ptr> m_events;
};

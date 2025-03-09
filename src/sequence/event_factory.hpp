#pragma once

#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "utils/string.hpp"
#include "templating/templated.hpp"

class Event;
class Parameter;
class Game_Facade;

// Uses the "abstract factory" pattern
class Event_Factory : public Templated
{
public:
	Event_Factory() = default;
	Event_Factory(Event_Factory&&) = delete;
	Event_Factory(const Event_Factory&) = delete;
	virtual ~Event_Factory() = default;

	virtual Own_Ptr<Event> make_event(Game_Facade&) = 0;
};

#pragma once

#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "utils/string.hpp"

class Event;
class Event_Parameter;
class Game_Facade;

// Uses the "abstract factory" pattern
class Event_Factory
{
public:
	Event_Factory() = default;
	Event_Factory(Event_Factory&&) = delete;
	Event_Factory(const Event_Factory&) = delete;

	virtual ~Event_Factory() = default;
	virtual Own_Ptr<Event> make_event(Game_Facade&) = 0;

	// Callable must take two arguments: const String&, Event_parameter&
	template<typename Callable>
	void for_each_parameter(Callable c);

protected:
	// Each derived class must register all of its parameters
	void register_parameter(const String& name, Event_Parameter&);

private:
	struct Registered_Parameter {
		String mame;
		Event_Parameter& parameter;
	};

	Array<Registered_Parameter> m_parameters;
};



// Implementation


template<typename Callable>
void Event_Factory::for_each_parameter(Callable callback)
{
	for (Registered_Parameter& param : m_parameters) {
		callback(param.mame, param.parameter);
	}
}

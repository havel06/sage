#include "event_factory.hpp"


void Event_Factory::register_parameter(const String& name, Event_Parameter& parameter)
{
	m_parameters.push_back(Registered_Parameter{name, parameter});
}

#include "condition_factory.hpp"


void Condition_Factory::register_parameter(const String& name, Parameter& parameter)
{
	m_parameters.push_back(Registered_Parameter{name, parameter});
}

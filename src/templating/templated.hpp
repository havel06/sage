#pragma once

#include "utils/array.hpp"
#include "utils/string.hpp"
#include "utils/concepts.hpp"

// fwd
class Parameter;

// An interface for anything that has templated parameters (events, conditions, widgets, etc)
class Templated
{
public:
	Templated() = default;
	Templated(Templated&&) = delete;
	Templated(const Templated&) = delete;
	virtual ~Templated() = default;

	template<typename Fn>
	requires Concepts::Callable<Fn, const String&, Parameter&>
	void for_each_parameter(Fn c);

protected:
	// Each derived class must register all of its parameters
	void register_parameter(const String& name, Parameter&);

private:
	struct Registered_Parameter {
		String mame;
		Parameter& parameter;
	};

	Array<Registered_Parameter> m_parameters;
};

// Implementation

template<typename Fn>
requires Concepts::Callable<Fn, const String&, Parameter&>
void Templated::for_each_parameter(Fn callback)
{
	for (Registered_Parameter& param : m_parameters) {
		callback(param.mame, param.parameter);
	}
}

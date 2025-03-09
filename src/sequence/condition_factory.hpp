#pragma once

#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "utils/string.hpp"
#include "utils/concepts.hpp"

class Condition;
class Parameter;
class Game_Facade;

// Uses the "abstract factory" pattern
class Condition_Factory
{
public:
	Condition_Factory() = default;
	Condition_Factory(Condition_Factory&&) = delete;
	Condition_Factory(const Condition_Factory&) = delete;

	virtual ~Condition_Factory() = default;
	virtual Own_Ptr<Condition> make_condition(Game_Facade&) = 0;

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
void Condition_Factory::for_each_parameter(Fn callback)
{
	for (Registered_Parameter& param : m_parameters) {
		callback(param.mame, param.parameter);
	}
}

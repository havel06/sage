#pragma once

#include "utils/own_ptr.hpp"
#include "templating/templated.hpp"

class Condition;
class Parameter;
class Game_Facade;

// Uses the "abstract factory" pattern
class Condition_Factory : public Templated
{
public:
	Condition_Factory() = default;
	Condition_Factory(Condition_Factory&&) = delete;
	Condition_Factory(const Condition_Factory&) = delete;

	virtual ~Condition_Factory() = default;
	virtual Own_Ptr<Condition> make_condition(Game_Facade&) = 0;
};

#pragma once
#include "utils/concepts.hpp"
#include "utils/function_wrapper.hpp"
#include "input_event.hpp"

class Input_Observer
{
public:
	virtual void handle_input_event(Input_Event) = 0;
};

class Input_Event_Provider
{
public:
	virtual void process(Input_Observer&) = 0;
};

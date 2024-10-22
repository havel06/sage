#pragma once
#include "utils/concepts.hpp"
#include "utils/function_wrapper.hpp"

enum class Input_Event
{
	down_pressed,
	down_released,
	up_pressed,
	up_released,
	left_pressed,
	left_released,
	right_pressed,
	right_released,
	accept,
	escape,
	open_inventory,
	open_quest_log,
};

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

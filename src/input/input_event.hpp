#pragma once

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

const char* input_event_to_string(Input_Event);
Input_Event input_event_from_string(const char*);

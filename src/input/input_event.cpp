#include "input_event.hpp"
#include <assert.h>
#include <string.h>

const char* input_event_to_string(Input_Event event)
{
	switch (event) {
		case Input_Event::down_pressed:
			return "down_pressed";
		case Input_Event::down_released:
			return "down_released";
		case Input_Event::up_pressed:
			return "up_pressed";
		case Input_Event::up_released:
			return "up_released";
		case Input_Event::left_pressed:
			return "left_pressed";
		case Input_Event::left_released:
			return "left_released";
		case Input_Event::right_pressed:
			return "right_pressed";
		case Input_Event::right_released:
			return "right_released";
		case Input_Event::accept:
			return "accept";
		case Input_Event::escape:
			return "escape";
		case Input_Event::open_inventory:
			return "open_inventory";
		case Input_Event::open_quest_log:
			return "open_quest_log";
	}
}

Input_Event input_event_from_string(const char* str)
{
	if (strcmp("down_pressed", str) == 0) {
		return Input_Event::down_pressed;
	}
	if (strcmp("down_released", str) == 0) {
		return Input_Event::down_released;
	}
	if (strcmp("up_pressed", str) == 0) {
		return Input_Event::up_pressed;
	}
	if (strcmp("up_released", str) == 0) {
		return Input_Event::up_released;
	}
	if (strcmp("left_pressed", str) == 0) {
		return Input_Event::left_pressed;
	}
	if (strcmp("left_released", str) == 0) {
		return Input_Event::left_released;
	}
	if (strcmp("right_pressed", str) == 0) {
		return Input_Event::right_pressed;
	}
	if (strcmp("right_released", str) == 0) {
		return Input_Event::right_released;
	}
	if (strcmp("accept", str) == 0) {
		return Input_Event::accept;
	}
	if (strcmp("escape", str) == 0) {
		return Input_Event::escape;
	}
	if (strcmp("open_inventory", str) == 0) {
		return Input_Event::open_inventory;
	}
	if (strcmp("open_quest_log", str) == 0) {
		return Input_Event::open_quest_log;
	}

	assert(false);
}

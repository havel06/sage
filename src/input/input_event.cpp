#include "input_event.hpp"

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

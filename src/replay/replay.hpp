#pragma once

#include "input/input_event.hpp"
#include "utils/array.hpp"

struct Replay_Event
{
	Input_Event input_event;
	double event_time;
};

struct Replay
{
	Array<Replay_Event> events;

	static Replay load_from_file(const char* filename);
	void save_to_file(const char* filename) const;
};

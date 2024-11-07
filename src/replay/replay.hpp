#pragma once

#include "input/input_event.hpp"
#include "utils/array.hpp"
#include "utils/optional.hpp"

struct Replay_Frame
{
	Array<Input_Event> input_events;
	float duration;
};

struct Replay
{
	Array<Replay_Frame> frames;

	static Replay load_from_file(const char* filename);
	void save_to_file(const char* filename) const;
};

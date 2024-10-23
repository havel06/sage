#pragma once

#include "input/input_event.hpp"
#include "utils/array.hpp"

// fwd
namespace JSON {
	class Object;
}

struct Replay_Event
{
	Input_Event input_event;
	double event_time;
};

class Replay_Recorder
{
public:
	void capture_event(Input_Event event, double event_time);
	void write_to_file(const char* filename);
private:
	JSON::Object serialise_event(const Replay_Event&);

	Array<Replay_Event> m_events;
};

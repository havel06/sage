#pragma once

#include "input/input_event.hpp"
#include "replay.hpp"

// fwd
namespace JSON {
	class Object;
}

class Replay_Recorder
{
public:
	void capture_event(Input_Event event, double event_time);
	const Replay& get_replay() { return m_replay; }
private:
	Replay m_replay;
};

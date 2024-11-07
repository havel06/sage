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
	void begin_frame(float dt);
	void capture_event(Input_Event event);
	const Replay& get_replay() { return m_replay; }
private:
	Replay m_replay;
};

#include "replay_recorder.hpp"
#include "input/input_event.hpp"

void Replay_Recorder::begin_frame(float dt)
{
	m_replay.frames.push_back(Replay_Frame{.duration = dt});
}

void Replay_Recorder::capture_event(Input_Event event)
{
	if (m_replay.frames.empty())
		return;

	m_replay.frames.back().input_events.push_back(event);
}

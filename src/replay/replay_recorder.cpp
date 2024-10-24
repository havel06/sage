#include "replay_recorder.hpp"
#include "input/input_event.hpp"

void Replay_Recorder::capture_event(Input_Event event, double event_time)
{
	m_replay.events.push_back(Replay_Event{
		.input_event = event,
		.event_time = event_time
	});
}

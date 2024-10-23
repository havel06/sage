#include "replay_recorder.hpp"
#include "input/input_event.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "utils/move.hpp"

void Replay_Recorder::capture_event(Input_Event event, double event_time)
{
	m_events.push_back(Replay_Event{
		.input_event = event,
		.event_time = event_time
	});
}

void Replay_Recorder::write_to_file(const char* filename)
{
	JSON::Array events_json;
	for (const Replay_Event& event : m_events) {
		events_json.add(serialise_event(event));
	}

	JSON::Object json;
	json.add("events", move(events_json));
	json.write_to_file(filename);
	SG_INFO("Saved replay file \"%s\"", filename);
}

JSON::Object Replay_Recorder::serialise_event(const Replay_Event& event)
{
	JSON::Object json;
	json.add("input", input_event_to_string(event.input_event));
	json.add("time", event.event_time);
	return json;
}

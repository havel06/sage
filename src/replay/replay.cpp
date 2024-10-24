#include "replay.hpp"
#include "utils/json.hpp"
#include "utils/move.hpp"
#include "utils/log.hpp"

Replay Replay::load_from_file(const char* filename)
{
	JSON::Object json = JSON::Object::from_file(filename);
	JSON::Array_View events = json.get_view().get("events").as_array();

	Replay replay;
	events.for_each([&](const JSON::Value_View& value){
		JSON::Object_View event_json = value.as_object();
		Replay_Event event = {
			.input_event = input_event_from_string(event_json.get("input").as_string("escape")),
			.event_time = event_json.get("time").as_double(0)
		};
		replay.events.push_back(move(event));
	});

	return replay;
}

void Replay::save_to_file(const char* filename) const
{
	JSON::Array events_json;
	for (const Replay_Event& event : events) {
		JSON::Object json;
		json.add("input", input_event_to_string(event.input_event));
		json.add("time", event.event_time);
		events_json.add(move(json));
	}

	JSON::Object json;
	json.add("events", move(events_json));
	json.write_to_file(filename);
	SG_INFO("Saved replay file \"%s\"", filename);
}

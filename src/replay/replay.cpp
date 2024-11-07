#include "replay.hpp"
#include "input/input_event.hpp"
#include "utils/json.hpp"
#include "utils/move.hpp"
#include "utils/log.hpp"

Replay Replay::load_from_file(const char* filename)
{
	JSON::Object json = JSON::Object::from_file(filename);
	JSON::Array_View frames = json.get_view().get("frames").as_array();

	Replay replay;
	frames.for_each([&](const JSON::Value_View& value){
		JSON::Object_View frame_json = value.as_object();

		Replay_Frame frame;
		frame.duration = frame_json.get("duration").as_float(0);

		frame_json.get("input").as_array().for_each([&](const JSON::Value_View& value){
			frame.input_events.push_back(input_event_from_string(value.as_string("escape")));
		});

		replay.frames.push_back(move(frame));
	});

	return replay;
}

void Replay::save_to_file(const char* filename) const
{
	JSON::Array frames_json;

	for (const Replay_Frame& frame : frames) {
		JSON::Object json;

		JSON::Array events_json;
		for (const Input_Event& event : frame.input_events) {
			events_json.add(input_event_to_string(event));
		}

		json.add("input", move(events_json));
		json.add("duration", frame.duration);
		frames_json.add(move(json));
	}

	JSON::Object json;
	json.add("frames", move(frames_json));
	json.write_to_file(filename);
	SG_INFO("Saved replay file \"%s\"", filename);
}

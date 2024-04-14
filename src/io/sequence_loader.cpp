#include "sequence_loader.hpp"
#include "cJSON.h"
#include "sequence/events/dummy.hpp"
#include "sequence/events/echo.hpp"
#include "sequence/events/change_map.hpp"
#include "utils/file.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"

Sequence Sequence_Loader::load(const String& filename)
{
	String content = read_file_to_str(filename.data());
	cJSON* json = cJSON_Parse(content.data());
	const cJSON* events = cJSON_GetObjectItem(json, "events");
	Sequence sequence;

	const cJSON* event_json;
	cJSON_ArrayForEach(event_json, events) {
		sequence.add_event(parse_event(event_json));
	}

	cJSON_Delete(json);
	return sequence;
}

// TODO - refactor to an event factory?
Event_Ptr Sequence_Loader::parse_event(const cJSON* json)
{
	const String type = cJSON_GetObjectItem(json, "type")->valuestring;
	const cJSON* params = cJSON_GetObjectItem(json, "parameters");

	if (type == "echo") {
		String message = cJSON_GetObjectItem(params, "message")->valuestring;
		return make_own_ptr<Events::Echo>((String&&)message);
	} else if (type == "change_map") {
		String map = cJSON_GetObjectItem(params, "map")->valuestring;
		return make_own_ptr<Events::Change_Map>((String&&)map);
	} else {
		SG_ERROR("Invalid event type \"%s\"", type.data());
		return make_own_ptr<Events::Dummy>();
	}
}

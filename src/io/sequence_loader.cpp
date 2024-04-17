#include "sequence_loader.hpp"
#include "cJSON.h"
#include "sequence/events/display_text.hpp"
#include "sequence/events/dummy.hpp"
#include "sequence/events/echo.hpp"
#include "sequence/events/change_map.hpp"
#include "sequence/events/give_item.hpp"
#include "sequence/events/teleport_player.hpp"
#include "utils/file.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"

Sequence Sequence_Loader::load(const String& filename)
{
	String content = read_file_to_str(filename.data());
	cJSON* json = cJSON_Parse(content.data());
	Sequence sequence;

	const cJSON* repeatable = cJSON_GetObjectItem(json, "repeatable");
	if (repeatable) {
		sequence.repeatable = repeatable->valueint;
	}

	const cJSON* events = cJSON_GetObjectItem(json, "events");

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
		const String message =
			cJSON_GetObjectItem(params, "message")->valuestring;
		return make_own_ptr<Events::Echo>((String&&)message);
	} else if (type == "display_text") {
		const String message =
			cJSON_GetObjectItem(params, "message")->valuestring;
		return make_own_ptr<Events::Display_Text>((String&&)message);
	} else if (type == "give_item") {
		const String id =
			cJSON_GetObjectItem(params, "item")->valuestring;
		const int count =
			cJSON_GetObjectItem(params, "count")->valueint;
		return make_own_ptr<Events::Give_Item>((String&&)id, count);
	} else if (type == "change_map") {
		const String map =
			cJSON_GetObjectItem(params, "map")->valuestring;
		return make_own_ptr<Events::Change_Map>((String&&)map);
	} else if (type == "teleport_player") {
		const int x = cJSON_GetObjectItem(params, "x")->valueint;
		const int y = cJSON_GetObjectItem(params, "y")->valueint;
		return make_own_ptr<Events::Teleport_Player>(Vec2i{x, y});
	} else {
		SG_WARNING("Invalid event type \"%s\"", type.data());
		return make_own_ptr<Events::Dummy>();
	}
}

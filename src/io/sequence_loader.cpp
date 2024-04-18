#include "sequence_loader.hpp"
#include "cJSON.h"
#include "io/resource_manager.hpp"
#include "sequence/events/change_sprite.hpp"
#include "sequence/events/display_text.hpp"
#include "sequence/events/dummy.hpp"
#include "sequence/events/echo.hpp"
#include "sequence/events/change_map.hpp"
#include "sequence/events/give_item.hpp"
#include "sequence/events/play_music.hpp"
#include "sequence/events/play_sound.hpp"
#include "sequence/events/teleport_player.hpp"
#include "sequence/events/teleport_entity.hpp"
#include "sequence/sequence.hpp"
#include "utils/file.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "cjson_types.hpp"

Sequence_Loader::Sequence_Loader(Resource_Manager& res_mgr) :
	m_resource_manager{res_mgr}
{

}

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
	Event_Ptr loaded_event;

	if (type == "echo") {
		const String message =
			cJSON_GetObjectItem(params, "message")->valuestring;
		loaded_event = make_own_ptr<Events::Echo>((String&&)message);
	} else if (type == "display_text") {
		const String message =
			cJSON_GetObjectItem(params, "message")->valuestring;
		loaded_event = make_own_ptr<Events::Display_Text>((String&&)message);
	} else if (type == "give_item") {
		const String id =
			cJSON_GetObjectItem(params, "item")->valuestring;
		const int count =
			cJSON_GetObjectItem(params, "count")->valueint;
		loaded_event = make_own_ptr<Events::Give_Item>((String&&)id, count);
	} else if (type == "change_map") {
		const String map =
			cJSON_GetObjectItem(params, "map")->valuestring;
		loaded_event = make_own_ptr<Events::Change_Map>((String&&)map);
	} else if (type == "teleport_player") {
		const int x = cJSON_GetObjectItem(params, "x")->valueint;
		const int y = cJSON_GetObjectItem(params, "y")->valueint;
		loaded_event = make_own_ptr<Events::Teleport_Player>(Vec2i{x, y});
	} else if (type == "teleport_entity") {
		const String name = cJSON_GetObjectItem(params, "entity")->valuestring;
		const int x = cJSON_GetObjectItem(params, "x")->valueint;
		const int y = cJSON_GetObjectItem(params, "y")->valueint;
		loaded_event = make_own_ptr<Events::Teleport_Entity>((String&&)name, Vec2i{x, y});
	} else if (type == "play_sound") {
		const char* filename = cJSON_GetObjectItem(params, "sound")->valuestring;
		Sound sound = m_resource_manager.get_sound(filename);
		loaded_event = make_own_ptr<Events::Play_Sound>(sound);
	} else if (type == "play_music") {
		const char* filename = cJSON_GetObjectItem(params, "music")->valuestring;
		Sound music = m_resource_manager.get_sound(filename);
		loaded_event = make_own_ptr<Events::Play_Music>(music);
	} else if (type == "change_sprite") {
		const String entity = cJSON_GetObjectItem(params, "entity")->valuestring;
		const cJSON* sprite_json = cJSON_GetObjectItem(params, "sprite");
		const Sprite sprite = cJSON_Types::parse_sprite(sprite_json, m_resource_manager);
		loaded_event = make_own_ptr<Events::Change_Sprite>((String&&)entity, sprite);
	} else {
		SG_WARNING("Invalid event type \"%s\"", type.data());
		loaded_event = make_own_ptr<Events::Dummy>();
	}

	const cJSON* asynchronous = cJSON_GetObjectItem(json, "asynchronous");
	if (asynchronous) {
		loaded_event->asynchronous = asynchronous->valueint;
	}

	return loaded_event;
}

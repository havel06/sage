#include "sequence_loader.hpp"
#include "cJSON.h"
#include "character_profile.hpp"
#include "io/resource_manager.hpp"
#include "sequence/conditions/has_item.hpp"
#include "sequence/conditions/not.hpp"
#include "sequence/events/activate_sequence.hpp"
#include "sequence/events/add_to_party.hpp"
#include "sequence/events/change_sprite.hpp"
#include "sequence/events/display_text.hpp"
#include "sequence/events/dummy.hpp"
#include "sequence/events/echo.hpp"
#include "sequence/events/change_map.hpp"
#include "sequence/events/give_item.hpp"
#include "sequence/events/move_entity.hpp"
#include "sequence/events/remove_item.hpp"
#include "sequence/events/play_music.hpp"
#include "sequence/events/play_sound.hpp"
#include "sequence/events/teleport_player.hpp"
#include "sequence/events/teleport_entity.hpp"
#include "sequence/events/enable_player_actions.hpp"
#include "sequence/events/disable_player_actions.hpp"
#include "sequence/events/enter_combat.hpp"
#include "sequence/sequence.hpp"
#include "utils/file.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "cjson_types.hpp"

Sequence_Loader::Sequence_Loader(Resource_Manager& res_mgr, Game_Facade& facade) :
	m_facade{facade},
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

	// Events
	const cJSON* events = cJSON_GetObjectItem(json, "events");
	const cJSON* event_json;
	cJSON_ArrayForEach(event_json, events) {
		sequence.add_event(parse_event(event_json));
	}

	// Condition
	const cJSON* condition_json = cJSON_GetObjectItem(json, "condition");
	if (condition_json) {
		sequence.set_condition(parse_condition(condition_json));
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
		loaded_event = make_own_ptr<Events::Echo>(m_facade, (String&&)message);
	} else if (type == "display_text") {
		const String message =
			cJSON_GetObjectItem(params, "message")->valuestring;
		loaded_event = make_own_ptr<Events::Display_Text>(m_facade, (String&&)message);
	} else if (type == "give_item") {
		const String id =
			cJSON_GetObjectItem(params, "item")->valuestring;
		const int count =
			cJSON_GetObjectItem(params, "count")->valueint;
		loaded_event = make_own_ptr<Events::Give_Item>(m_facade, (String&&)id, count);
	} else if (type == "remove_item") {
		const String id =
			cJSON_GetObjectItem(params, "item")->valuestring;
		const int count =
			cJSON_GetObjectItem(params, "count")->valueint;
		loaded_event = make_own_ptr<Events::Remove_Item>(m_facade, (String&&)id, count);
	} else if (type == "change_map") {
		const String map =
			cJSON_GetObjectItem(params, "map")->valuestring;
		loaded_event = make_own_ptr<Events::Change_Map>(m_facade, (String&&)map);
	} else if (type == "teleport_player") {
		const int x = cJSON_GetObjectItem(params, "x")->valueint;
		const int y = cJSON_GetObjectItem(params, "y")->valueint;
		loaded_event = make_own_ptr<Events::Teleport_Player>(m_facade, Vec2i{x, y});
	} else if (type == "teleport_entity") {
		const String name = cJSON_GetObjectItem(params, "entity")->valuestring;
		const int x = cJSON_GetObjectItem(params, "x")->valueint;
		const int y = cJSON_GetObjectItem(params, "y")->valueint;
		loaded_event = make_own_ptr<Events::Teleport_Entity>(m_facade, (String&&)name, Vec2i{x, y});
	} else if (type == "move_entity") {
		const String name = cJSON_GetObjectItem(params, "entity")->valuestring;
		const int x = cJSON_GetObjectItem(params, "x")->valueint;
		const int y = cJSON_GetObjectItem(params, "y")->valueint;
		loaded_event = make_own_ptr<Events::Move_Entity>(m_facade, (String&&)name, Vec2i{x, y});
	} else if (type == "play_sound") {
		const char* filename = cJSON_GetObjectItem(params, "sound")->valuestring;
		Sound sound = m_resource_manager.get_sound(filename);
		loaded_event = make_own_ptr<Events::Play_Sound>(m_facade, sound);
	} else if (type == "play_music") {
		const char* filename = cJSON_GetObjectItem(params, "music")->valuestring;
		Sound music = m_resource_manager.get_sound(filename);
		loaded_event = make_own_ptr<Events::Play_Music>(m_facade, music);
	} else if (type == "change_sprite") {
		const String entity = cJSON_GetObjectItem(params, "entity")->valuestring;
		const cJSON* sprite_json = cJSON_GetObjectItem(params, "sprite");
		const Sprite sprite = cJSON_Types::parse_sprite(sprite_json, m_resource_manager);
		loaded_event = make_own_ptr<Events::Change_Sprite>(m_facade, (String&&)entity, sprite);
	} else if (type == "activate_sequence") {
		const char* sequence_src = cJSON_GetObjectItem(params, "sequence")->valuestring;
		Sequence& sequence = m_resource_manager.get_sequence(sequence_src);
		loaded_event = make_own_ptr<Events::Activate_Sequence>(m_facade, sequence);
	} else if (type == "add_to_party") {
		const char* character_src = cJSON_GetObjectItem(params, "character")->valuestring;
		Character_Profile character = m_resource_manager.get_character_profile(character_src);
		loaded_event = make_own_ptr<Events::Add_To_Party>(m_facade, character);
	} else if (type == "enable_player_actions") {
		loaded_event = make_own_ptr<Events::Enable_Player_Actions>(m_facade);
	} else if (type == "disable_player_actions") {
		loaded_event = make_own_ptr<Events::Disable_Player_Actions>(m_facade);
	} else if (type == "enter_combat") {
		const cJSON* enemies_json = cJSON_GetObjectItem(params, "enemies");
		const cJSON* enemy_json;
		Array<Character_Profile> enemies;
		cJSON_ArrayForEach(enemy_json, enemies_json) {
			Character_Profile enemy = m_resource_manager.get_character_profile(enemy_json->valuestring);
			enemies.push_back(enemy);
		}
		loaded_event = make_own_ptr<Events::Enter_Combat>(m_facade, (Array<Character_Profile>&&)enemies);
	} else {
		SG_WARNING("Invalid event type \"%s\"", type.data());
		loaded_event = make_own_ptr<Events::Dummy>(m_facade);
	}

	const cJSON* asynchronous = cJSON_GetObjectItem(json, "asynchronous");
	if (asynchronous) {
		loaded_event->asynchronous = asynchronous->valueint;
	}

	return loaded_event;
}

Condition_Ptr Sequence_Loader::parse_condition(const cJSON* json)
{
	const String type = cJSON_GetObjectItem(json, "type")->valuestring;
	const cJSON* params = cJSON_GetObjectItem(json, "parameters");

	if (type == "has_item") {
		String item = cJSON_GetObjectItem(params, "item")->valuestring;
		const int count = cJSON_GetObjectItem(params, "count")->valueint;
		return make_own_ptr<Conditions::Has_Item>(m_facade, (String&&)item, count);
	} else if (type == "not") {
		Condition_Ptr sub_condition = parse_condition(cJSON_GetObjectItem(params, "condition"));
		return make_own_ptr<Conditions::Not>(m_facade, (Condition_Ptr&&)sub_condition);
	} else {
		SG_WARNING("Invalid event type \"%s\"", type.data());
		return nullptr;
	}
}

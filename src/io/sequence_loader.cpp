#include "sequence_loader.hpp"
#include "character_profile.hpp"
#include "combat/battle_desc.hpp"
#include "graphics/ui/layout.hpp"
#include "io/gui_loader.hpp"
#include "utils/move.hpp"
#include "sequence/conditions/has_item.hpp"
#include "sequence/conditions/not.hpp"
#include "sequence/events/activate_sequence.hpp"
#include "sequence/events/add_quest.hpp"
#include "sequence/events/finish_quest.hpp"
#include "sequence/events/add_to_party.hpp"
#include "sequence/events/delay.hpp"
#include "sequence/events/change_sprite.hpp"
#include "sequence/events/display_text.hpp"
#include "sequence/events/dummy.hpp"
#include "sequence/events/echo.hpp"
#include "sequence/events/change_map.hpp"
#include "sequence/events/give_item.hpp"
#include "sequence/events/move_entity.hpp"
#include "sequence/events/remove_item.hpp"
#include "sequence/events/rotate_entity.hpp"
#include "sequence/events/play_music.hpp"
#include "sequence/events/play_sound.hpp"
#include "sequence/events/show_gui.hpp"
#include "sequence/events/hide_gui.hpp"
#include "sequence/events/teleport_player.hpp"
#include "sequence/events/teleport_entity.hpp"
#include "sequence/events/enable_player_actions.hpp"
#include "sequence/events/disable_player_actions.hpp"
#include "sequence/events/enter_combat.hpp"
#include "sequence/events/zoom_camera.hpp"
#include "sequence/sequence.hpp"
#include "utils/direction.hpp"
#include "utils/file.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "json_types.hpp"
#include "resource/resource_system.hpp"

Sequence_Loader::Sequence_Loader(Resource_System& res_system, Game_Facade& facade, GUI_Loader& gui_loader) :
	m_facade{facade},
	m_resource_system{res_system},
	m_gui_loader{gui_loader}
{
}

Sequence Sequence_Loader::load(const String& filename)
{
	SG_DEBUG("Parsing sequence %s", filename.data());

	const JSON::Object json = JSON::Object::from_file(filename.data());
	const JSON::Object_View view = json.get_view();
	Sequence sequence(filename);

	if (view.has("repeatable")) {
		sequence.repeatable = view["repeatable"].as_bool();
	}

	// Events
	view["events"].as_array().for_each([&](const JSON::Value_View& event) {
		sequence.add_event(parse_event(event.as_object()));
	});

	// Condition
	if (view.has("condition")) {
		sequence.set_condition(parse_condition(view["condition"].as_object()));
	}

	return sequence;
}

// TODO - refactor to an event factory?
Event_Ptr Sequence_Loader::parse_event(const JSON::Object_View& json)
{
	const String type= json["type"].as_string();
	const JSON::Object_View params = json["parameters"].as_object();
	Event_Ptr loaded_event;

	if (type == "echo") {
		const String message = params["message"].as_string();
		loaded_event = make_own_ptr<Events::Echo>(m_facade, (String&&)message);
	} else if (type == "display_text") {
		const String message = params["message"].as_string();
		loaded_event = make_own_ptr<Events::Display_Text>(m_facade, (String&&)message);
	} else if (type == "delay") {
		const float seconds = params["seconds"].as_float();
		loaded_event = make_own_ptr<Events::Delay>(m_facade, seconds);
	} else if (type == "give_item") {
		const String id = params["item"].as_string();
		const int count = params["count"].as_int();
		loaded_event = make_own_ptr<Events::Give_Item>(m_facade, (String&&)id, count);
	} else if (type == "remove_item") {
		const String id = params["item"].as_string();
		const int count = params["count"].as_int();
		loaded_event = make_own_ptr<Events::Remove_Item>(m_facade, (String&&)id, count);
	} else if (type == "change_map") {
		const String map = params["map"].as_string();
		loaded_event = make_own_ptr<Events::Change_Map>(m_facade, (String&&)map);
	} else if (type == "teleport_player") {
		const int x = params["x"].as_int();
		const int y = params["y"].as_int();
		loaded_event = make_own_ptr<Events::Teleport_Player>(m_facade, Vec2i{x, y});
	} else if (type == "teleport_entity") {
		const String name = params["entity"].as_string();
		const int x = params["x"].as_int();
		const int y = params["y"].as_int();
		loaded_event = make_own_ptr<Events::Teleport_Entity>(m_facade, (String&&)name, Vec2i{x, y});
	} else if (type == "move_entity") {
		const String name = params["entity"].as_string();
		const int x = params["x"].as_int();
		const int y = params["y"].as_int();
		loaded_event = make_own_ptr<Events::Move_Entity>(m_facade, (String&&)name, Vec2i{x, y});
	} else if (type == "rotate_entity") {
		const String name = params["entity"].as_string();
		const Direction dir = direction_from_string(params["direction"].as_string());
		loaded_event = make_own_ptr<Events::Rotate_Entity>(m_facade, (String&&)name, dir);
	} else if (type == "play_sound") {
		const char* filename = params["sound"].as_string();
		Sound sound = m_resource_system.sound_manager.get(filename, false);
		loaded_event = make_own_ptr<Events::Play_Sound>(m_facade, sound);
	} else if (type == "play_music") {
		const char* filename = params["music"].as_string();
		Sound music = m_resource_system.sound_manager.get(filename, false);
		loaded_event = make_own_ptr<Events::Play_Music>(m_facade, music);
	} else if (type == "change_sprite") {
		const String entity = params["entity"].as_string();
		const Sprite sprite = JSON_Types::parse_sprite(params["sprite"].as_object(), m_resource_system.texture_manager);
		loaded_event = make_own_ptr<Events::Change_Sprite>(m_facade, (String&&)entity, sprite);
	} else if (type == "activate_sequence") {
		const char* sequence_src = params["sequence"].as_string();
		Sequence& sequence = m_resource_system.sequence_manager.get(sequence_src, false);
		loaded_event = make_own_ptr<Events::Activate_Sequence>(m_facade, sequence);
	} else if (type == "add_to_party") {
		const char* character_src = params["character"].as_string();
		Character_Profile character = m_resource_system.character_profile_manager.get(character_src, false);
		loaded_event = make_own_ptr<Events::Add_To_Party>(m_facade, character);
	} else if (type == "add_quest") {
		String id = params["id"].as_string();
		String name = params["name"].as_string();
		String desc = params["description"].as_string();
		loaded_event = make_own_ptr<Events::Add_Quest>(m_facade, (String&&)id, (String&&)name, (String&&)desc);
	} else if (type == "finish_quest") {
		String id = params["id"].as_string();
		loaded_event = make_own_ptr<Events::Finish_Quest>(m_facade, (String&&)id);
	} else if (type == "zoom_camera") {
		const int amount = params["zoom"].as_int();
		loaded_event = make_own_ptr<Events::Zoom_Camera>(m_facade, amount);
	} else if (type == "enable_player_actions") {
		loaded_event = make_own_ptr<Events::Enable_Player_Actions>(m_facade);
	} else if (type == "disable_player_actions") {
		loaded_event = make_own_ptr<Events::Disable_Player_Actions>(m_facade);
	} else if (type == "show_gui") {
		UI::Widget_Ptr widget = m_gui_loader.load(params["widget"].as_string());
		loaded_event = make_own_ptr<Events::Show_GUI>(m_facade, move(widget));
	} else if (type == "hide_gui") {
		loaded_event = make_own_ptr<Events::Hide_GUI>(m_facade);
	} else if (type == "enter_combat") {
		const char* win_sequence_path = params["win_sequence"].as_string();
		const char* lose_sequence_path = params["lose_sequence"].as_string();
		Sequence& win_sequence = m_resource_system.sequence_manager.get(win_sequence_path, false);
		Sequence& lose_sequence = m_resource_system.sequence_manager.get(lose_sequence_path, false);
		Array<Character_Profile> enemies;
		params["enemies"].as_array().for_each([&](const JSON::Value_View& value){
			Character_Profile enemy = m_resource_system.character_profile_manager.get(value.as_string(), false);
			enemies.push_back(enemy);
		});
		Battle_Description battle_desc{(Array<Character_Profile>&&)enemies, win_sequence, lose_sequence};
		loaded_event = make_own_ptr<Events::Enter_Combat>(m_facade, (Battle_Description&&)battle_desc);
	} else {
		SG_WARNING("Invalid event type \"%s\"", type.data());
		loaded_event = make_own_ptr<Events::Dummy>(m_facade);
	}

	if (json.has("asynchronous")) {
		loaded_event->asynchronous = json["asynchronous"].as_bool();
	}

	return loaded_event;
}

Condition_Ptr Sequence_Loader::parse_condition(const JSON::Object_View& json)
{
	const String type = json["type"].as_string();
	const JSON::Object_View params = json["parameters"].as_object();

	if (type == "has_item") {
		String item = params["item"].as_string();
		const int count = params["count"].as_int();
		return make_own_ptr<Conditions::Has_Item>(m_facade, (String&&)item, count);
	} else if (type == "not") {
		Condition_Ptr sub_condition = parse_condition(params["condition"].as_object());
		return make_own_ptr<Conditions::Not>(m_facade, (Condition_Ptr&&)sub_condition);
	} else {
		SG_WARNING("Invalid event type \"%s\"", type.data());
		return nullptr;
	}
}

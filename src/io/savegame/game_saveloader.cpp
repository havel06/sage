#include "game_saveloader.hpp"
#include "character_profile.hpp"
#include "game/game.hpp"
#include "graphics/animated_sprite.hpp"
#include "graphics/scriptable_gui.hpp"
#include "io/character_profile_loader.hpp"
#include "io/json_types.hpp"
#include "io/resource/resource_handle.hpp"
#include "io/savegame/inventory_saveloader.hpp"
#include "io/savegame/quest_saveloader.hpp"
#include "io/user_directory_provider.hpp"
#include "item/inventory.hpp"
#include "sequence/sequence.hpp"
#include "utils/filesystem.hpp"
#include "utils/file.hpp"
#include "utils/log.hpp"
#include "game/game_facade.hpp"
#include "graphics/camera.hpp"
#include "io/resource/sequence_manager.hpp"
#include "game/game_logic_state_normal.hpp"
#include "utils/json.hpp"
#include <stdio.h>

Game_Saveloader::Game_Saveloader(User_Directory_Provider& dir_provider, const String& project_dir, Game_Logic_State_Normal& logic_normal, Camera_Controller& camera, Inventory& inv, Quest_Log& quest_log, Sequence_Manager& seq_manager, Character_Profile_Manager& character_manager, Party& party, Scriptable_GUI& gui, Combat& combat, Texture_Manager& tex_mgr, Game_Logic& logic) :
	m_logic{logic},
	m_logic_normal{logic_normal},
	m_camera_controller{camera},
	m_inventory{inv},
	m_quest_log{quest_log},
	m_seq_manager{seq_manager},
	m_user_dir_provider{dir_provider},
	m_character_manager{character_manager},
	m_texture_manager{tex_mgr},
	m_party{party},
	m_scriptable_gui{gui},
	m_combat{combat}
{
	m_project_dir = project_dir;
}

String Game_Saveloader::get_savefile_path()
{
	String save_file_path = m_user_dir_provider.get_savegame_path();
	save_file_path.append("/save.json");
	return save_file_path;
}

void Game_Saveloader::save()
{
	String map_absolute_path = m_logic_normal.get_map_filename();

	if (map_absolute_path.empty())
		return;

	JSON::Object json;

	String map_relative_path = get_relative_path(map_absolute_path, m_project_dir);
	json.add("current_map", map_relative_path.data());
	json.add("camera_zoom", m_camera_controller.get_zoom());

	json.add("camera_x", JSON::Value{m_camera_controller.get_camera_position().x});
	json.add("camera_y", JSON::Value{m_camera_controller.get_camera_position().y});
	const bool camera_fixed = m_camera_controller.get_mode() == Camera_Controller_Mode::fixed;
	json.add("camera_fixed", camera_fixed);

	Inventory_Saveloader inv_saveloader;
	json.add("inventory", inv_saveloader.save(m_inventory));
	Quest_Saveloader quest_saveloader(m_quest_log);
	json.add("quests", quest_saveloader.save());
	json.add("active_sequences", serialise_active_sequences());
	json.add("party", serialise_party());
	json.add("player_actions_disabled", m_logic_normal.player_actions_disabled);

	if (!m_scriptable_gui.get_current_widget_filename().empty()) {
		json.add("scriptable_gui_widget", m_scriptable_gui.get_current_widget_filename().data());
	}

	if (m_combat.is_active()) {
		json.add("battle", serialise_battle(m_combat.get_battle()));
	}
	
	// Write to file
	String savefile_path = get_savefile_path();
	create_directories_for_file(savefile_path);
	json.write_to_file(savefile_path.data());

	SG_INFO("Saved game state.");
}

void Game_Saveloader::load()
{
	String savefile_path = get_savefile_path();
	if (!file_exists(savefile_path))
		return;

	JSON::Object json = JSON::Object::from_file(savefile_path.data());
	JSON::Object_View view = json.get_view();

	const char* current_map = view["current_map"].as_string(m_logic_normal.get_map_filename().data());
	m_logic_normal.set_current_map(current_map);

	m_camera_controller.set_zoom(view["camera_zoom"].as_float(m_camera_controller.get_zoom()));
	// Camera
	{
		const float x = view["camera_x"].as_float(m_camera_controller.get_camera_position().x);
		const float y = view["camera_y"].as_float(m_camera_controller.get_camera_position().y);

		if (view["camera_fixed"].as_bool(false))
			m_camera_controller.set_fixed_target_instant(Vec2f{x, y});
		else
			m_camera_controller.teleport_to(Vec2f{x, y});
	}

	Inventory_Saveloader inv_saveloader;
	inv_saveloader.load(m_inventory, view["inventory"].as_array());
	Quest_Saveloader quest_saveloader(m_quest_log);
	quest_saveloader.load(view["quests"].as_array());
	load_active_sequences(view["active_sequences"].as_array());
	load_party(view["party"].as_array());
	m_logic_normal.player_actions_disabled = view["player_actions_disabled"].as_bool(false);

	if (view.has("scriptable_gui_widget")) {
		m_scriptable_gui.show_widget(view["scriptable_gui_widget"].as_string(""));
	}

	if (view.has("battle")) {
		load_battle(view["battle"].as_object());
	}

	SG_INFO("Loaded game state.");
}

void Game_Saveloader::new_game()
{
	String savefile_path = get_savefile_path();
	if (!file_exists(savefile_path))
		return;

	String folder = remove_filename(savefile_path);
	remove_directory(folder);
}

JSON::Object Game_Saveloader::serialise_battle(const Battle& battle)
{
	JSON::Object json;

	// Enemies
	JSON::Array enemies_json;
	for (int i = 0; i < battle.get_enemy_count(); i++) {
		const Combat_Unit& enemy = battle.get_enemy(i);
		String path = get_relative_path(enemy.character.get_path(), m_project_dir);
		enemies_json.add(path.data());
	}
	json.add("enemies", move(enemies_json));

	// Sequences
	String win_sequence_path =
		get_relative_path(battle.get_description().win_sequence.get_path(), m_project_dir);
	String lose_sequence_path =
		get_relative_path(battle.get_description().lose_sequence.get_path(), m_project_dir);

	json.add("win_sequence", win_sequence_path.data());
	json.add("lose_sequence", lose_sequence_path.data());
	json.add(
		"background",
		JSON_Types::serialise_animated_sprite(
			battle.get_description().background,
			m_project_dir
		)
	);

	return json;
}

JSON::Array Game_Saveloader::serialise_active_sequences()
{
	JSON::Array json;

	m_seq_manager.for_each([&](const String& path, const Sequence& sequence){
		if (sequence.is_active()) {
			String rel_path = get_relative_path(path.data(), m_project_dir);
			json.add(rel_path.data());
		}
	});

	return json;
}

void Game_Saveloader::load_active_sequences(const JSON::Array_View& json)
{
	json.for_each([&](const JSON::Value_View& value){
		m_seq_manager.get(value.as_string(""), false).get().try_activate();
	});
}

JSON::Array Game_Saveloader::serialise_party()
{
	JSON::Array json;

	for (int i = 0; i < m_party.get_character_count(); i++) {
		const Character_Profile& profile = m_party.get_character(i).get();
		if (&profile != &m_party.main_character().get())
			json.add(profile.filename.data());
	}

	return json;
}

void Game_Saveloader::load_party(const JSON::Array_View& json)
{
	json.for_each([&](const JSON::Value_View& value){
		auto profile = m_character_manager.get(value.as_string(""), true);
		m_party.add_character(profile);
	});
}

void Game_Saveloader::load_battle(const JSON::Object_View& json)
{
	SG_DEBUG("Saveloader - loading battle");
	Array<Resource_Handle<Character_Profile>> enemies;
	json.get("enemies").as_array().for_each([&](const JSON::Value_View& value){
		enemies.push_back(m_character_manager.get(value.as_string(""), false));
	});

	Resource_Handle<Sequence> win_seq =
		m_seq_manager.get(json.get("win_sequence").as_string(""), false);

	Resource_Handle<Sequence> lose_seq =
		m_seq_manager.get(json.get("lose_sequence").as_string(""), false);

	Animated_Sprite background = 
		JSON_Types::parse_animated_sprite(json.get("background").as_object(), m_texture_manager);

	Battle_Description description {
		.enemies = move(enemies),
		.win_sequence = win_seq,
		.lose_sequence = lose_seq,
		.background = move(background)
	};

	m_logic.enter_combat(description);
}

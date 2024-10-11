#include "game_saveloader.hpp"
#include "character_profile.hpp"
#include "game/game.hpp"
#include "io/character_profile_loader.hpp"
#include "io/savegame/inventory_saveloader.hpp"
#include "io/savegame/quest_saveloader.hpp"
#include "io/user_directory_provider.hpp"
#include "item/inventory.hpp"
#include "utils/filesystem.hpp"
#include "utils/file.hpp"
#include "utils/log.hpp"
#include "game/game_facade.hpp"
#include "graphics/camera.hpp"
#include "io/resource/sequence_manager.hpp"
#include "game/game_logic_state_normal.hpp"
#include "utils/json.hpp"
#include <stdio.h>

Game_Saveloader::Game_Saveloader(User_Directory_Provider& dir_provider, const String& project_dir, Game_Logic_State_Normal& logic, Game_Camera& camera, Inventory& inv, Quest_Log& quest_log, Sequence_Manager& seq_manager, Character_Profile_Manager& character_manager, Party& party) :
	m_logic{logic},
	m_camera{camera},
	m_inventory{inv},
	m_quest_log{quest_log},
	m_seq_manager{seq_manager},
	m_savegame_dir_provider{dir_provider},
	m_character_manager{character_manager},
	m_party{party}
{
	m_project_dir = project_dir;
}

String Game_Saveloader::get_savefile_path()
{
	String save_file_path = m_savegame_dir_provider.get_savegame_path();
	save_file_path.append("/save.json");
	return save_file_path;
}

void Game_Saveloader::save()
{
	String map_absolute_path = m_logic.get_map_filename();

	if (map_absolute_path.empty())
		return;

	JSON::Object json;

	String map_relative_path = get_relative_path(map_absolute_path, m_project_dir);
	json.add("current_map", map_relative_path.data());
	json.add("camera_zoom", m_camera.zoom);
	Inventory_Saveloader inv_saveloader;
	json.add("inventory", inv_saveloader.save(m_inventory));
	Quest_Saveloader quest_saveloader(m_quest_log);
	json.add("quests", quest_saveloader.save());
	json.add("active_sequences", serialise_active_sequences());
	json.add("party", serialise_party());
	json.add("player_actions_disabled", m_logic.player_actions_disabled);
	
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

	const char* current_map = view["current_map"].as_string(m_logic.get_map_filename().data());
	m_logic.set_current_map(current_map);

	m_camera.zoom = view["camera_zoom"].as_float(m_camera.zoom);
	Inventory_Saveloader inv_saveloader;
	inv_saveloader.load(m_inventory, view["inventory"].as_array());
	Quest_Saveloader quest_saveloader(m_quest_log);
	quest_saveloader.load(view["quests"].as_array());
	load_active_sequences(view["active_sequences"].as_array());
	load_party(view["party"].as_array());
	m_logic.player_actions_disabled = view["player_actions_disabled"].as_bool(false);

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

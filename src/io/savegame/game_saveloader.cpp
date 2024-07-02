#include "game_saveloader.hpp"
#include "io/savegame/inventory_saveloader.hpp"
#include "io/savegame/quest_saveloader.hpp"
#include "io/savegame/savegame_directory_provider.hpp"
#include "item/inventory.hpp"
#include "utils/filesystem.hpp"
#include "utils/file.hpp"
#include "utils/log.hpp"
#include "game/game_facade.hpp"
#include "graphics/camera.hpp"
#include "io/resource/sequence_manager.hpp"
#include "utils/json.hpp"
#include <stdio.h>

Game_Saveloader::Game_Saveloader(Savegame_Directory_Provider& dir_provider, const String& project_dir, Game_Facade& facade, Game_Camera& camera, Inventory& inv, Quest_Log& quest_log, Sequence_Manager& seq_manager) :
	m_game_facade{facade},
	m_camera{camera},
	m_inventory{inv},
	m_quest_log{quest_log},
	m_seq_manager{seq_manager},
	m_savegame_dir_provider{dir_provider}
{
	m_project_dir = project_dir;
}

String Game_Saveloader::get_savefile_path()
{
	String save_file_path = m_savegame_dir_provider.get_path();
	save_file_path.append("/save.json");
	return save_file_path;
}

void Game_Saveloader::save()
{
	String map_absolute_path = m_game_facade.get_current_map_path();

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

	const char* current_map = view["current_map"].as_string();
	m_game_facade.set_current_map(current_map);

	m_camera.zoom = view["camera_zoom"].as_float();
	Inventory_Saveloader inv_saveloader;
	inv_saveloader.load(m_inventory, view["inventory"].as_array());
	Quest_Saveloader quest_saveloader(m_quest_log);
	quest_saveloader.load(view["quests"].as_array());
	load_active_sequences(view["active_sequences"].as_array());

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

	m_seq_manager.for_each([&](const Sequence& sequence){
		if (sequence.is_active()) {
			String path = get_relative_path(sequence.get_path().data(), m_project_dir);
			json.add(path.data());
		}
	});

	return json;
}

void Game_Saveloader::load_active_sequences(const JSON::Array_View& json)
{
	json.for_each([&](const JSON::Value_View& value){
		m_seq_manager.get(value.as_string(), false).try_activate();
	});
}

#include "game_saveloader.hpp"
#include "io/savegame/inventory_saveloader.hpp"
#include "io/savegame/quest_saveloader.hpp"
#include "item/inventory.hpp"
#include "utils/filesystem.hpp"
#include "utils/file.hpp"
#include "utils/log.hpp"
#include "game_facade.hpp"
#include "graphics/camera.hpp"
#include <stdio.h>
#include <cJSON.h>

Game_Saveloader::Game_Saveloader(const String& project_dir, Game_Facade& facade, Game_Camera& camera, Inventory& inv, Quest_Log& quest_log) :
	m_game_facade{facade},
	m_camera{camera},
	m_inventory{inv},
	m_quest_log{quest_log}
{
	m_project_dir = project_dir;
}

void Game_Saveloader::set_save_directory(const String& path)
{
	m_savefile_path = path;
	m_savefile_path.append("/save.json");

	create_directory(path);
}

void Game_Saveloader::save()
{
	String map_absolute_path = m_game_facade.get_current_map_path();

	if (map_absolute_path.empty())
		return;

	// Create JSON
	cJSON* json = cJSON_CreateObject();
	String map_relative_path = get_relative_path(map_absolute_path, m_project_dir);
	cJSON_AddItemToObject(json, "current_map", cJSON_CreateString(map_relative_path.data()));
	cJSON_AddItemToObject(json, "camera_zoom", cJSON_CreateNumber(m_camera.zoom));
	Inventory_Saveloader inv_saveloader;
	cJSON_AddItemToObject(json, "inventory", inv_saveloader.save(m_inventory));
	Quest_Saveloader quest_saveloader(m_quest_log);
	cJSON_AddItemToObject(json, "quests", quest_saveloader.save());
	
	// Write to file
	create_directories_for_file(m_savefile_path);
	FILE* f = fopen(m_savefile_path.data(), "w");
	assert(f);
	char* json_str = cJSON_Print(json);
	fputs(json_str, f);
	free(json_str);
	fclose(f);

	// Delete JSON
	cJSON_Delete(json);

	SG_INFO("Saved game state.");
}

void Game_Saveloader::load()
{
	if (!file_exists(m_savefile_path))
		return;

	String file_contents = read_file_to_str(m_savefile_path.data());
	cJSON* json = cJSON_Parse(file_contents.data());

	const char* current_map = cJSON_GetObjectItem(json, "current_map")->valuestring;
	m_game_facade.set_current_map(current_map);
	m_camera.zoom = cJSON_GetObjectItem(json, "camera_zoom")->valuedouble;
	Inventory_Saveloader inv_saveloader;
	inv_saveloader.load(m_inventory, cJSON_GetObjectItem(json, "inventory"));
	Quest_Saveloader quest_saveloader(m_quest_log);
	quest_saveloader.load(cJSON_GetObjectItem(json, "quests"));

	cJSON_Delete(json);
	SG_INFO("Loaded game state.");
}

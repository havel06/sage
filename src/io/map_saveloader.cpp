#include "map_saveloader.hpp"
#include "cJSON.h"
#include "io/cjson_types.hpp"
#include "utils/direction.hpp"
#include "utils/filesystem.hpp"
#include "map/map.hpp"
#include "utils/log.hpp"
#include "stdio.h"

Map_Saveloader::Map_Saveloader(const String& project_dir)
{
	m_project_dir = project_dir;
}

void Map_Saveloader::set_save_directory(const String& path)
{
	// Create maps directory if needed
	m_saved_maps_dir = path;
	m_saved_maps_dir.append("/maps");

	if (!directory_exists(m_saved_maps_dir)) {
		create_directory(m_saved_maps_dir);
		SG_INFO("Created directory \"%s\".", m_saved_maps_dir.data());
	}
}

void Map_Saveloader::save(const Map& map)
{
	// FIXME - refactor function
	assert(!m_project_dir.empty());
	assert(!m_saved_maps_dir.empty());

	if (map.get_path().empty()) {
		return;
	}

	String savefile_path = get_savefile_location(map.get_path());

	// Create json
	cJSON* json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "entities", serialise_entities(map.entities));

	// Write file
	create_directories_for_file(savefile_path);
	FILE* f = fopen(savefile_path.data(), "w");
	assert(f);
	char* json_str = cJSON_Print(json);
	fputs(json_str, f);
	free(json_str);
	fclose(f);

	// Delete json
	cJSON_Delete(json);

	SG_INFO("Saved state of map \"%s\".", map.get_path().data());
}

void Map_Saveloader::load(Map& map)
{
	assert(!m_project_dir.empty());
	assert(!m_saved_maps_dir.empty());

	if (map.get_path().empty()) {
		return;
	}

	SG_INFO("Loaded state of map \"%s\".", map.get_path().data());
}

String Map_Saveloader::get_savefile_location(const String& map_path)
{
	String relative_path = get_relative_path(map_path, m_project_dir);
	String save_file_path = m_saved_maps_dir;
	save_file_path.append("/");
	save_file_path.append(relative_path);

	return save_file_path;
}

cJSON* Map_Saveloader::serialise_entities(const Map_Entities& entities)
{
	cJSON* array = cJSON_CreateArray();

	for (int i = 0; i < entities.get_entity_count(); i++) {
		const Entity& entity = entities.get_entity(i);
		cJSON_AddItemToArray(array, serialise_entity(entity));
	}

	return array;
}

cJSON* Map_Saveloader::serialise_entity(const Entity& entity)
{
	cJSON* entity_json = cJSON_CreateObject();

	cJSON_AddItemToObject(entity_json, "name", cJSON_CreateString(entity.name.data()));
	cJSON_AddItemToObject(entity_json, "x", cJSON_CreateNumber(entity.position.x));
	cJSON_AddItemToObject(entity_json, "y", cJSON_CreateNumber(entity.position.y));
	cJSON_AddItemToObject(entity_json, "direction", cJSON_CreateString(direction_to_string(entity.get_look_direction())));

	if (!entity.sprite.is_null())
		cJSON_AddItemToObject(entity_json, "sprite", cJSON_Types::serialise_sprite(entity.sprite));

	return entity_json;
}

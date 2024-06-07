#include "map_saveloader.hpp"
#include "cJSON.h"
#include "io/json_types.hpp"
#include "utils/direction.hpp"
#include "utils/file.hpp"
#include "utils/filesystem.hpp"
#include "map/map.hpp"
#include "utils/log.hpp"
#include "stdio.h"

Map_Saveloader::Map_Saveloader(Texture_Manager& tex_mgr, const String& project_dir) :
	m_texture_manager{tex_mgr}
{
	m_project_dir = project_dir;
}

void Map_Saveloader::set_save_directory(const String& path)
{
	// Create maps directory if needed
	m_saved_maps_dir = path;
	m_saved_maps_dir.append("/maps");

	create_directory(m_saved_maps_dir);
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

	String savefile_path = get_savefile_location(map.get_path());

	if (!file_exists(savefile_path)) {
		return;
	}

	String file_contents = read_file_to_str(savefile_path.data());
	cJSON* json = cJSON_Parse(file_contents.data());
	deserialise_entites(map.entities, cJSON_GetObjectItem(json, "entities"));
	cJSON_Delete(json);

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
	cJSON_AddItemToObject(entity_json, "moving", cJSON_CreateBool(entity.is_moving()));

	if (!entity.sprite.is_null())
		cJSON_AddItemToObject(entity_json, "sprite", JSON_Types::serialise_sprite(entity.sprite, m_project_dir));

	return entity_json;
}

void Map_Saveloader::deserialise_entity(Entity& entity, const cJSON* entity_json)
{
	entity.position.x = cJSON_GetObjectItem(entity_json, "x")->valueint;
	entity.position.y = cJSON_GetObjectItem(entity_json, "y")->valueint;

	const cJSON* sprite_json = cJSON_GetObjectItem(entity_json, "sprite");
	if (sprite_json)
		entity.sprite = JSON_Types::parse_sprite(sprite_json, m_texture_manager);

	entity.look(direction_from_string(cJSON_GetObjectItem(entity_json, "direction")->valuestring));

	if (cJSON_GetObjectItem(entity_json, "moving")->valueint) {
		entity.move(entity.get_look_direction());
	}
}

void Map_Saveloader::deserialise_entites(Map_Entities& entities, const cJSON* json)
{
	assert(json);

	cJSON* entity_json = nullptr;
	cJSON_ArrayForEach(entity_json, json) {
		const char* name = cJSON_GetObjectItem(entity_json, "name")->valuestring;
		Entity* entity = entities.get_entity(name);
		if (entity) {
			deserialise_entity(*entity, entity_json);
		} else {
			SG_ERROR("Savegame loading - unable to find entity \"%s\".", name);
		}
	}
}

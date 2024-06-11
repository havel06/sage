#include "map_saveloader.hpp"
#include "io/json_types.hpp"
#include "utils/direction.hpp"
#include "utils/file.hpp"
#include "utils/filesystem.hpp"
#include "map/map.hpp"
#include "utils/json.hpp"
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

	JSON::Object json;
	json.add("entities", serialise_entities(map.entities));

	String savefile_path = get_savefile_location(map.get_path());
	create_directories_for_file(savefile_path);
	json.write_to_file(savefile_path.data());

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

	JSON::Object json = JSON::Object::from_file(savefile_path.data());
	JSON::Object_View view = json.get_view();
	deserialise_entites(map.entities, view["entities"].as_array());

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

JSON::Array Map_Saveloader::serialise_entities(const Map_Entities& entities)
{
	JSON::Array array;

	for (int i = 0; i < entities.get_entity_count(); i++) {
		const Entity& entity = entities.get_entity(i);
		array.add(serialise_entity(entity));
	}

	return array;
}

JSON::Object Map_Saveloader::serialise_entity(const Entity& entity)
{
	JSON::Object json;

	json.add("name", entity.name.data());
	json.add("x", entity.position.x);
	json.add("y", entity.position.y);
	json.add("direction", direction_to_string(entity.get_look_direction()));
	json.add("moving", entity.is_moving());

	if (!entity.sprite.is_null()) {
		json.add("sprite", JSON_Types::serialise_sprite(entity.sprite, m_project_dir));
	}

	return json;
}

void Map_Saveloader::deserialise_entity(Entity& entity, const JSON::Object_View& entity_json)
{
	entity.position.x = entity_json["x"].as_int();
	entity.position.y = entity_json["y"].as_int();

	if (entity_json.has("sprite")) {
		const JSON::Object_View& sprite_json = entity_json["sprite"].as_object();
		entity.sprite = JSON_Types::parse_sprite(sprite_json, m_texture_manager);
	}

	entity.look(direction_from_string(entity_json["direction"].as_string()));

	if (entity_json["moving"].as_bool()) {
		entity.move(entity.get_look_direction());
	}
}

void Map_Saveloader::deserialise_entites(Map_Entities& entities, const JSON::Array_View& json)
{
	json.for_each([&](const JSON::Value_View& value){
		const JSON::Object_View entity_json = value.as_object();

		const char* name = entity_json["name"].as_string();
		Entity* entity = entities.get_entity(name);

		if (entity) {
			deserialise_entity(*entity, entity_json);
		} else {
			SG_ERROR("Savegame loading - unable to find entity \"%s\".", name);
		}
	});
}

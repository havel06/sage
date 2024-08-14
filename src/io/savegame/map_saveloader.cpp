#include "map_saveloader.hpp"
#include "io/json_types.hpp"
#include "utils/direction.hpp"
#include "utils/file.hpp"
#include "utils/filesystem.hpp"
#include "map/map.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "io/savegame/savegame_directory_provider.hpp"

Map_Saveloader::Map_Saveloader(Texture_Manager& tex_mgr, Savegame_Directory_Provider& dir_provider, const String& project_dir) :
	m_savegame_dir_provider{dir_provider},
	m_texture_manager{tex_mgr}
{
	m_project_dir = project_dir;
}

void Map_Saveloader::save(const Map& map, const String& path)
{
	if (path.empty())
		return;

	// FIXME - refactor function
	assert(!m_project_dir.empty());

	JSON::Object json;
	json.add("entities", serialise_entities(map.entities));

	String savefile_path = get_savefile_location(path);
	create_directories_for_file(savefile_path);
	json.write_to_file(savefile_path.data());

	SG_INFO("Saved state of map \"%s\".", path.data());
}

void Map_Saveloader::load(Map& map, const String& path)
{
	if (path.empty())
		return;

	assert(!m_project_dir.empty());

	String savefile_path = get_savefile_location(path);

	if (!file_exists(savefile_path)) {
		return;
	}

	JSON::Object json = JSON::Object::from_file(savefile_path.data());
	JSON::Object_View view = json.get_view();
	deserialise_entites(map.entities, view["entities"].as_array());

	SG_INFO("Loaded state of map \"%s\".", path.data());
}

String Map_Saveloader::get_savefile_location(const String& map_path)
{
	String path_relative_to_project = get_relative_path(map_path, m_project_dir);

	String save_file_path = m_savegame_dir_provider.get_path();
	save_file_path.append("/maps/");
	save_file_path.append(path_relative_to_project);

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

	json.add("sprite", JSON_Types::serialise_animated_sprite(entity.sprite, m_project_dir));

	return json;
}

void Map_Saveloader::deserialise_entity(Entity& entity, const JSON::Object_View& entity_json)
{
	entity.position.x = entity_json["x"].as_int(0);
	entity.position.y = entity_json["y"].as_int(0);

	if (entity_json.has("sprite")) {
		const JSON::Object_View& sprite_json = entity_json["sprite"].as_object();
		entity.sprite = JSON_Types::parse_animated_sprite(sprite_json, m_texture_manager);
	}

	entity.look(direction_from_string(entity_json["direction"].as_string("down")));

	if (entity_json["moving"].as_bool(false)) {
		entity.move(entity.get_look_direction());
	}
}

void Map_Saveloader::deserialise_entites(Map_Entities& entities, const JSON::Array_View& json)
{
	json.for_each([&](const JSON::Value_View& value){
		const JSON::Object_View entity_json = value.as_object();

		const char* name = entity_json["name"].as_string("");
		Entity* entity = entities.get_entity(name);

		if (entity) {
			deserialise_entity(*entity, entity_json);
		} else {
			SG_ERROR("Savegame loading - unable to find entity \"%s\".", name);
		}
	});
}

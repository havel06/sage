#pragma once

#include "utils/string.hpp"

// fwd
class Map;
class Map_Entities;
class Tile_Layers;
class Tile_Layer;
class Entity;
class Texture_Manager;
class User_Directory_Provider;
namespace JSON {
	class Object_View;
	class Array_View;
	class Object;
	class Array;
}

// Saves and loads player progress in maps
// FIXME - this might not be the best name
class Map_Saveloader
{
public:
	Map_Saveloader(Texture_Manager&, User_Directory_Provider&, const String& project_dir);

	void save(const Map&, const String& path);
	void load(Map&, const String& path);
private:
	String get_savefile_location(const String& map_path);

	JSON::Array serialise_entities(const Map_Entities&);
	JSON::Object serialise_entity(const Entity&);
	JSON::Array serialise_layers(const Tile_Layers&);
	JSON::Object serialise_layer(const Tile_Layer&);

	void deserialise_entites(Map_Entities&, const JSON::Array_View& entities);
	void deserialise_entity(Entity&, const JSON::Object_View& entity_json);
	void deserialise_layers(Tile_Layers&, const JSON::Array_View& layers);
	void deserialise_layer(Tile_Layer&, const JSON::Object_View& layer_json);
	
	User_Directory_Provider& m_user_dir_provider;
	Texture_Manager& m_texture_manager;
	String m_project_dir;
};

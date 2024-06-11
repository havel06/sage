#pragma once

#include "utils/string.hpp"

// fwd
class Map;
class Map_Entities;
class Entity;
class Texture_Manager;
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
	Map_Saveloader(Texture_Manager&, const String& project_dir);
	void set_save_directory(const String& path);

	void save(const Map&);
	void load(Map&);
private:
	String get_savefile_location(const String& map_path);

	JSON::Array serialise_entities(const Map_Entities&); // Returns a JSON array
	JSON::Object serialise_entity(const Entity&); // Returns a JSON object

	void deserialise_entites(Map_Entities&, const JSON::Array_View& entities);
	void deserialise_entity(Entity&, const JSON::Object_View& entity_json);

	Texture_Manager& m_texture_manager;
	String m_project_dir;
	String m_saved_maps_dir;
};

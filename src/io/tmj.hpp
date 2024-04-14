#pragma once

#include "map/map.hpp"
#include "utils/string.hpp"
#include "raylib/raylib.h"

class cJSON;
class Resource_Manager;

namespace TMJ
{

class Tileset
{
public:
	Tileset(int first_id, Vec2i tile_size, int columns, const Texture&);
private:
	int m_first_id;
	Vec2i m_tile_size;
	int m_columns;
	Texture m_texture;
};

class Map_Loader
{
public:
	Map_Loader(Resource_Manager&, const String& path);
	Map retrieve_map();
private:
	void parse_layer_array(const cJSON* layer);
	void parse_layer(const cJSON* layer);
	void parse_tile_layer(const cJSON* layer);
	void parse_object_layer(const cJSON* layer);
	void parse_tileset(const cJSON* layer);

	String m_path;
	Resource_Manager& m_resource_manager;
	Map m_map;
	Array<Tileset> m_tilesets;
};

}

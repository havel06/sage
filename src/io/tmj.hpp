#pragma once

#include "map/map.hpp"
#include "utils/string.hpp"
#include "raylib/raylib.h"

struct cJSON;
class Resource_Manager;

namespace TMJ
{

class Tileset
{
public:
	Tileset(Vec2i tile_size, int columns, int count, const Texture&);
	Tile get_tile(int index) const;
	void set_passable(int index, bool value);
private:
	Array<Tile> m_tiles;
};

struct Tileset_In_Map
{
	int first_id;
	Tileset tileset;
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
	void parse_object(const cJSON* object);
	void parse_tilesets(const cJSON* tilesets);
	Tileset parse_tileset(const char* tileset_filename);
	Tile resolve_tile(int tile_index);

	String relative_to_real_path(const char* relative_path);

	String m_path;
	Resource_Manager& m_resource_manager;
	Map m_map;
	int m_tile_width;
	int m_tile_height;
	Array<Tileset_In_Map> m_tilesets;
};

}

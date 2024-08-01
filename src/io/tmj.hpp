#pragma once

#include "map/map.hpp"
#include "utils/string.hpp"
#include "raylib/raylib.h"

//fwd
struct cJSON;
namespace JSON {
	class Object_View;
	class Array_View;
}
class Resource_System;

namespace TMJ
{

class Tileset
{
public:
	Tileset(Vec2i tile_size, int columns, int count, Resource_Handle<Sage_Texture>);
	Tileset();
	bool is_image_collection() const { return m_is_image_collection; }
	void add_tile(Tile);
	Tile get_tile(int index) const;
	void set_passable(int index, bool value);
private:
	bool m_is_image_collection;
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
	Map_Loader(Resource_System&, const String& path);
	Own_Ptr<Map> retrieve_map();
private:
	//void parse_properties(const cJSON*);
	void parse_layer_array(const JSON::Array_View& layer);
	void parse_layer(const JSON::Object_View& layer);
	void parse_tile_layer(const JSON::Object_View& layer);
	void parse_object_layer(const JSON::Object_View& layer);
	void parse_object(const JSON::Object_View& object);
	void parse_tilesets(const JSON::Array_View& tilesets);
	Tileset parse_tileset(const char* tileset_filename);
	void parse_tile_properties(const JSON::Array_View& properties, int id, Tileset& tileset);
	Tile resolve_tile(int tile_index);

	String m_path;
	Resource_System& m_resource_system;
	Own_Ptr<Map> m_map;
	int m_tile_width;
	int m_tile_height;
	Array<Tileset_In_Map> m_tilesets;
};

}

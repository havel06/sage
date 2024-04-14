#include "tmj.hpp"
#include "cJSON.h"
#include "io/resource_manager.hpp"
#include "utils/string.hpp"
#include "utils/log.hpp"
#include "utils/file.hpp"
#include <string.h>

namespace TMJ
{

Tileset::Tileset(int first_id, Vec2i tile_size, int columns, const Texture& texture)
{
	m_first_id = first_id;
	m_tile_size = tile_size;
	m_columns = columns;
	m_texture = texture;
}

Map_Loader::Map_Loader(Resource_Manager& res_mgr, const String& path) :
	m_resource_manager{res_mgr}
{
	m_path = path;

	String file_content = read_file_to_str(m_path.data());

	cJSON* json = cJSON_Parse(file_content.data());
	const int width = cJSON_GetObjectItem(json, "width")->valueint;
	const int height = cJSON_GetObjectItem(json, "height")->valueint;
	cJSON* layers = cJSON_GetObjectItem(json, "layers");

	m_map.resize(width, height);
	parse_layer_array(layers); // TODO - return this somewhere

	cJSON_Delete(json);
}

Map Map_Loader::retrieve_map()
{
	return m_map;
}

void Map_Loader::parse_layer_array(const cJSON* layer_array)
{
	const cJSON* layer_json;
	cJSON_ArrayForEach(layer_json, layer_array) {
		parse_layer(layer_json);
	}
}

void Map_Loader::parse_layer(const cJSON* layer_json)
{
	LOG_DEBUG("Parsing TMJ layer...");

	const cJSON* type = cJSON_GetObjectItem(layer_json, "type");

	if (strcmp(type->valuestring, "tilelayer") == 0) {
		parse_tile_layer(layer_json);
	} else if (strcmp(type->valuestring, "objectgroup") == 0) {
		parse_object_layer(layer_json);
	} else if (strcmp(type->valuestring, "group") == 0) {
		cJSON* layers = cJSON_GetObjectItem(layer_json, "layers");
		parse_layer_array(layers);
	} else {
		LOG_WARNING("Image layers are not supported.");
	}
}

void Map_Loader::parse_tile_layer(const cJSON* layer_json)
{
	// TODO
	(void)layer_json;
}

void Map_Loader::parse_object_layer(const cJSON* layer_json)
{
	// TODO
	(void)layer_json;
}

void Map_Loader::parse_tileset(const cJSON* tileset_json)
{
	LOG_DEBUG("Parsing TMJ tileset...");

	const int first_id = cJSON_GetObjectItem(tileset_json, "firstgid")->valueint;
	const int columns = cJSON_GetObjectItem(tileset_json, "columns")->valueint;
	const int tile_width = cJSON_GetObjectItem(tileset_json, "tilewidth")->valueint;
	const int tile_height = cJSON_GetObjectItem(tileset_json, "tileheight")->valueint;
	const char* image_relative = cJSON_GetObjectItem(tileset_json, "image")->valuestring;

	String image_path = remove_filename(m_path); // Containing folder
	image_path.append('/');
	image_path.append(image_relative);

	Texture texture = m_resource_manager.get_texture(image_path.data());

	m_tilesets.push_back(Tileset{
		first_id,
		Vec2i{tile_width, tile_height},
		columns,
		texture
	});
}

}


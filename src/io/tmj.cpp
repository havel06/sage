#include "tmj.hpp"
#include "cJSON.h"
#include "io/resource_manager.hpp"
#include "map/tile_layer.hpp"
#include "utils/string.hpp"
#include "utils/log.hpp"
#include "utils/file.hpp"
#include <string.h>

namespace TMJ
{

Tileset::Tileset(Vec2i tile_size, int columns, const Texture& texture)
{
	m_tile_size = tile_size;
	m_columns = columns;
	m_texture = texture;
}

Tile Tileset::get_tile(int index) const
{
	Sprite sprite{m_texture};
	//SG_DEBUG("%d", m_texture.id);

	sprite.texture_clip.position.x = (index % m_columns) * m_tile_size.x;
	sprite.texture_clip.position.y = (index / m_columns) * m_tile_size.y;
	sprite.texture_clip.size = m_tile_size;

	return Tile {
		.sprite = sprite
	};
}

Map_Loader::Map_Loader(Resource_Manager& res_mgr, const String& path) :
	m_resource_manager{res_mgr}
{
	m_path = path;

	//SG_DEBUG("Opening map file \"%s\"", m_path.data());
	String file_content = read_file_to_str(m_path.data());

	cJSON* json = cJSON_Parse(file_content.data());
	const int width = cJSON_GetObjectItem(json, "width")->valueint;
	const int height = cJSON_GetObjectItem(json, "height")->valueint;
	cJSON* layers = cJSON_GetObjectItem(json, "layers");
	cJSON* tilesets = cJSON_GetObjectItem(json, "tilesets");

	m_map.resize(width, height);
	parse_tilesets(tilesets);
	parse_layer_array(layers);

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
	//SG_DEBUG("Parsing TMJ layer...");

	const cJSON* type = cJSON_GetObjectItem(layer_json, "type");

	if (strcmp(type->valuestring, "tilelayer") == 0) {
		parse_tile_layer(layer_json);
	} else if (strcmp(type->valuestring, "objectgroup") == 0) {
		parse_object_layer(layer_json);
	} else if (strcmp(type->valuestring, "group") == 0) {
		cJSON* layers = cJSON_GetObjectItem(layer_json, "layers");
		parse_layer_array(layers);
	} else {
		SG_WARNING("Image layers are not supported.");
	}
}

void Map_Loader::parse_tile_layer(const cJSON* layer_json)
{
	const cJSON* indices = cJSON_GetObjectItem(layer_json, "data");

	int position_index = 0;
	const cJSON* tile_index;
	Tile_Layer layer(m_map.get_width(), m_map.get_height());

	cJSON_ArrayForEach(tile_index, indices) {
		if (tile_index->valueint != 0) {
			int y = position_index / m_map.get_width();
			int x = position_index % m_map.get_width();
			Tile tile = resolve_tile(tile_index->valueint);
			layer.set_tile({x, y}, tile);
		}
		position_index++;
	}

	m_map.add_layer((Tile_Layer&&)layer);
}

void Map_Loader::parse_object_layer(const cJSON* layer_json)
{
	// TODO
	(void)layer_json;
}

void Map_Loader::parse_tilesets(const cJSON* tilesets)
{
	const cJSON* tileset;
	cJSON_ArrayForEach(tileset, tilesets) {
		const int first_id = cJSON_GetObjectItem(tileset, "firstgid")->valueint;
		const char* src = cJSON_GetObjectItem(tileset, "source")->valuestring;

		m_tilesets.push_back(Tileset_In_Map{
			.first_id = first_id,
			.tileset = parse_tileset(src)
		});
	}
}

Tileset Map_Loader::parse_tileset(const char* tileset_filename_relative)
{
	//SG_DEBUG("Parsing TMJ tileset...");
	String tileset_path = relative_to_real_path(tileset_filename_relative);
	cJSON* tileset_json = cJSON_Parse(read_file_to_str(tileset_path.data()).data());

	const int columns = cJSON_GetObjectItem(tileset_json, "columns")->valueint;
	const int tile_width = cJSON_GetObjectItem(tileset_json, "tilewidth")->valueint;
	const int tile_height = cJSON_GetObjectItem(tileset_json, "tileheight")->valueint;
	const char* image_relative = cJSON_GetObjectItem(tileset_json, "image")->valuestring;

	String image_path = relative_to_real_path(image_relative);
	Texture texture = m_resource_manager.get_texture(image_path.data(), true);

	cJSON_Delete(tileset_json);

	SG_DEBUG("Loaded tileset \"%s\"", tileset_path.data());

	return Tileset{
		Vec2i{tile_width, tile_height},
		columns,
		texture
	};
}

String Map_Loader::relative_to_real_path(const char* relative_path)
{
	String result = remove_filename(m_path); // Containing folder
	result.append('/');
	result.append(relative_path);
	return result;
}

Tile Map_Loader::resolve_tile(int index)
{
	// Find corresponding tileset
	int tileset_index = 0;
	if (m_tilesets.size() > 1) {
		for (; tileset_index < m_tilesets.size(); tileset_index++) {
			if (m_tilesets[tileset_index].first_id > index) {
				break;
			}
		}
		tileset_index--;
	}
	//SG_DEBUG("Tileset index: %d", tileset_index);

	const int index_within_tileset = index - m_tilesets[tileset_index].first_id;
	return m_tilesets[tileset_index].tileset.get_tile(index_within_tileset);
}

}


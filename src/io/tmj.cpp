#include "tmj.hpp"
#include "graphics/animated_sprite.hpp"
#include "map/tile_layer.hpp"
#include "utils/direction.hpp"
#include "utils/string.hpp"
#include "utils/log.hpp"
#include "utils/file.hpp"
#include "utils/json.hpp"
#include "utils/filesystem.hpp"
#include "utils/profiler.hpp"
#include "resource/resource_system.hpp"

namespace TMJ
{

Tileset::Tileset(Vec2i tile_size, int columns, int count, Resource_Handle<Sage_Texture> texture) :
	m_columns{columns},
	m_tile_size{tile_size},
	m_texture{texture}
{

	m_tiles.resize(count);
	for (int i = 0; i < count; i++) {
		m_tiles[i].sprite = create_sprite_from_tile_id(i);
	}

	m_is_image_collection = false;
}

Tileset::Tileset()
{
	m_is_image_collection = true;
}

void Tileset::add_tile(Tile tile)
{
	m_tiles.push_back(tile);
}

Tile Tileset::get_tile(int index) const
{
	return m_tiles[index];
}

void Tileset::set_passable(int index, bool value)
{
	assert(index >= 0);
	assert(index < m_tiles.size());
	m_tiles[index].passable = value;
}

void Tileset::set_animation(int index, const Array<int>& frame_ids, float frame_time)
{
	assert(index >= 0);
	assert(index < m_tiles.size());

	Array<Sprite> frames;

	for (int frame_id : frame_ids) {
		frames.push_back(create_sprite_from_tile_id(frame_id));
	}

	m_tiles[index].sprite = Animated_Sprite{frames, frame_time};
}

Sprite Tileset::create_sprite_from_tile_id(int id)
{
	assert(m_texture.has_value());

	Sprite sprite(m_texture.value());
	sprite.texture_clip.position.x = (id % m_columns) * m_tile_size.x;
	sprite.texture_clip.position.y = (id / m_columns) * m_tile_size.y;
	sprite.texture_clip.size = m_tile_size;
	return sprite;
}

Map_Loader::Map_Loader(Resource_System& res_system, const String& path) :
	m_resource_system{res_system}
{
	SG_PROFILE_SCOPE("TMJ Map load");
	SG_DEBUG("Parsing map \"%s\"", path.data());
	m_path = path;

	JSON::Object json = [&](){
		SG_PROFILE_SCOPE("TMJ JSON parse");
		return JSON::Object::from_file(m_path.data());
	}();

	JSON::Object_View view = json.get_view();

	const int width = view["width"].as_int(0);
	const int height = view["height"].as_int(0);
	m_tile_width = view["tilewidth"].as_int(1);
	m_tile_height = view["tileheight"].as_int(1);

	m_map = make_own_ptr<Map>();
	m_map->resize(width, height);

	//parse_properties(cJSON_GetObjectItem(json, "properties"));
	parse_tilesets(view["tilesets"].as_array());
	parse_layer_array(view["layers"].as_array());
}

Own_Ptr<Map> Map_Loader::retrieve_map()
{
	return (Own_Ptr<Map>&&)(m_map);
}

void Map_Loader::parse_layer_array(const JSON::Array_View& layer_array)
{
	layer_array.for_each([&](const JSON::Value_View& layer){
		parse_layer(layer.as_object());
	});
}

void Map_Loader::parse_layer(const JSON::Object_View& layer_json)
{
	//SG_DEBUG("Parsing TMJ layer...");

	const String type = layer_json["type"].as_string("");

	if (type == "tilelayer") {
		parse_tile_layer(layer_json);
	} else if (type == "objectgroup") {
		parse_object_layer(layer_json);
	} else if (type == "group") {
		parse_layer_array(layer_json["layers"].as_array());
	} else if (type == "imagelayer") {
		SG_ERROR("Image layers are not supported.");
	} else {
		SG_ERROR("Unknown layer type \"%s\"", type.data());
	}
}

void Map_Loader::parse_tile_layer(const JSON::Object_View& layer_json)
{
	SG_PROFILE_SCOPE("TMJ Tile layer load");
	int position_index = 0;
	Tile_Layer layer(m_map->get_width(), m_map->get_height());

	layer_json["data"].as_array().for_each([&](const JSON::Value_View& index){
		int y = position_index / m_map->get_width();
		int x = position_index % m_map->get_width();

		if (index.as_int(0) == 0) {
			Tile empty_tile;
			empty_tile.passable = true;
			layer.set_tile({x, y}, empty_tile);
		} else {
			Tile tile = resolve_tile(index.as_int(0));
			layer.set_tile({x, y}, tile);
		}

		position_index++;
	});

	m_map->layers.add_layer((Tile_Layer&&)layer);
}

void Map_Loader::parse_object_layer(const JSON::Object_View& layer_json)
{
	SG_PROFILE_SCOPE("TMJ Object layer load");
	layer_json["objects"].as_array().for_each([&](const JSON::Value_View& object_json){
		parse_object(object_json.as_object());
	});
}

void Map_Loader::parse_object(const JSON::Object_View& object)
{
	Entity entity;

	entity.name = object["name"].as_string("");
	if (entity.name.empty()) {
		SG_ERROR("All entities must have a name.");
		assert(false);
	}
	entity.position.x = round(object["x"].as_float(0) / m_tile_width);
	entity.position.y = round(object["y"].as_float(0) / m_tile_height);
	entity.size.x = object["width"].as_int(1) / m_tile_width;
	entity.size.y = object["height"].as_int(1) / m_tile_height;

	if (object.has("gid")) {
		// Tile object
		Tile tile = resolve_tile(object["gid"].as_int(0));
		entity.sprite = tile.sprite;
		// NOTE - For some reason, tile objects have origin in the bottom left corner.
		entity.position.y -= entity.size.y;
	}

	if (object.has("properties")) {
		object["properties"].as_array().for_each([&](const JSON::Value_View& value){
			const JSON::Object_View property = value.as_object();

			const String name = property["name"].as_string("");
			if (name == "sequence") {
				const char* sequence_name = property["value"].as_string("");
				String sequence_path = resolve_relative_path(sequence_name, m_path);
				entity.assigned_sequence = m_resource_system.sequence_manager.get(sequence_path.data(), true);
			} else if (name == "character") {
				const char* character_relative = property["value"].as_string("");
				String character_path = resolve_relative_path(character_relative, m_path);
				entity.assigned_character = m_resource_system.character_profile_manager.get(character_path.data(), true);
			} else if (name == "passable") {
				entity.passable = property["value"].as_bool(false);
			} else if (name == "area_trigger") {
				entity.area_trigger = property["value"].as_bool(false);
			} else if (name == "direction") {
				entity.look(direction_from_string(property["value"].as_string("down")));
			} else {
				SG_WARNING("Object property \"%s\" is not supported.", name.data());
			}
		});
	}

	m_map->entities.add_entity((Entity&&)entity);
}

void Map_Loader::parse_tilesets(const JSON::Array_View& tilesets)
{
	tilesets.for_each([&](const JSON::Value_View& tileset){
		const int first_id = tileset.as_object()["firstgid"].as_int(0);
		const char* src = tileset.as_object()["source"].as_string("");
		m_tilesets.push_back(Tileset_In_Map{
			.first_id = first_id,
			.tileset = parse_tileset(src)
		});
	});
}

Tileset Map_Loader::parse_tileset(const char* tileset_filename_relative)
{
	// FIXME - refactor this function a bit

	SG_DEBUG("Parsing TMJ tileset \"%s\"", tileset_filename_relative);
	String tileset_path = resolve_relative_path(tileset_filename_relative, m_path);
	JSON::Object json = JSON::Object::from_file(tileset_path.data());
	JSON::Object_View view = json.get_view();

	const int columns = view["columns"].as_int(0);
	const int tilecount = view["tilecount"].as_int(0);
	const int tile_width = view["tilewidth"].as_int(0);
	const int tile_height = view["tileheight"].as_int(0);

	Tileset tileset = [&](){
		if (view.has("image")) {
			// Tileset from one image
			const char* image_relative = view["image"].as_string("");
			String image_path = resolve_relative_path(image_relative, tileset_path);
			Resource_Handle<Sage_Texture> texture = m_resource_system.texture_manager.get(image_path.data(), true);
			return Tileset{
				Vec2i{tile_width, tile_height},
				columns,
				tilecount,
				texture
			};
		} else {
			// Image collection tileset
			return Tileset{};
		}
	}();

	if (view.has("tiles")) {
		view["tiles"].as_array().for_each([&](const JSON::Value_View& value){
			JSON::Object_View tile = value.as_object();

			if (tileset.is_image_collection()) {
				const char* image_relative = tile["image"].as_string("");
				String image_path = resolve_relative_path(image_relative, tileset_path);
				Resource_Handle<Sage_Texture> texture = m_resource_system.texture_manager.get(image_path.data(), true);
				Sprite sprite{texture};
				tileset.add_tile(Tile{sprite});
			}

			if (tile.has("properties")) {
				const int id = tile["id"].as_int(0);
				parse_tile_properties(tile["properties"].as_array(), id, tileset);
			}

			if (tile.has("animation")) {
				const int id = tile["id"].as_int(0);
				parse_tile_animation(tile["animation"].as_array(), id, tileset);
			}
		});
	}
	
	SG_DEBUG("Loaded tileset \"%s\"", tileset_path.data());
	return tileset;
}

void Map_Loader::parse_tile_properties(const JSON::Array_View& properties, int id, Tileset& tileset)
{
	properties.for_each([&](const JSON::Value_View& property){
		String name = property.as_object()["name"].as_string("");
		if (name == "passable") {
			const bool value = property.as_object()["value"].as_bool(false);
			tileset.set_passable(id, value);
		} else {
			SG_WARNING("Tile property \"%s\" is not supported.", name.data());
		}
	});
}

void Map_Loader::parse_tile_animation(const JSON::Array_View& frames, int id, Tileset& tileset)
{
	int frame_time_ms = 0;
	Array<int> frame_tile_ids;

	frames.for_each([&](const JSON::Value_View& value){
		JSON::Object_View frame = value.as_object();
		frame_time_ms = frame["duration"].as_int(1000);
		frame_tile_ids.push_back(frame["tileid"].as_int(0));
	});

	tileset.set_animation(id, frame_tile_ids, (float)frame_time_ms / 1000);
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


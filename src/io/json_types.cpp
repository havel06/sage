#include "json_types.hpp"
#include "utils/filesystem.hpp"
#include "io/resource/texture_manager.hpp"
#include "utils/json.hpp"

namespace JSON_Types
{

Sprite parse_sprite(const JSON::Object_View& json, Texture_Manager& texture_manager)
{
	// FIXME - error handling
	const char* texture_name = json["texture"].as_string();
	const Sage_Texture texture = texture_manager.get(texture_name, false);

	Sprite sprite(texture);
	sprite.texture_clip.position.x = json["position_x"].as_int();
	sprite.texture_clip.position.y = json["position_y"].as_int();
	sprite.texture_clip.size.x = json["size_x"].as_int();
	sprite.texture_clip.size.y = json["size_y"].as_int();

	return sprite;
}

cJSON* serialise_sprite(const Sprite& sprite, const String& project_dir)
{
	assert(!sprite.get_texture_path().empty());

	String texture_relative_path = get_relative_path(sprite.get_texture_path(), project_dir);

	cJSON* json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "texture", cJSON_CreateString(texture_relative_path.data()));
	cJSON_AddItemToObject(json, "position_x", cJSON_CreateNumber(sprite.texture_clip.position.x));
	cJSON_AddItemToObject(json, "position_y", cJSON_CreateNumber(sprite.texture_clip.position.y));
	cJSON_AddItemToObject(json, "size_x", cJSON_CreateNumber(sprite.texture_clip.size.x));
	cJSON_AddItemToObject(json, "size_y", cJSON_CreateNumber(sprite.texture_clip.size.y));

	return json;
}

}

#include "cjson_types.hpp"
#include "cJSON.h"
#include "utils/filesystem.hpp"
#include "io/resource/texture_manager.hpp"

namespace cJSON_Types
{

Sprite parse_sprite(const cJSON* json, Texture_Manager& texture_manager)
{
	assert(json);
	const char* texture_name = cJSON_GetObjectItem(json, "texture")->valuestring;
	const Sage_Texture texture = texture_manager.get(texture_name, false);
	Sprite sprite(texture);
	sprite.texture_clip.position.x = cJSON_GetObjectItem(json, "position_x")->valueint;
	sprite.texture_clip.position.y = cJSON_GetObjectItem(json, "position_y")->valueint;
	sprite.texture_clip.size.x = cJSON_GetObjectItem(json, "size_x")->valueint;
	sprite.texture_clip.size.y = cJSON_GetObjectItem(json, "size_y")->valueint;

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

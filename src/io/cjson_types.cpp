#include "cjson_types.hpp"
#include "cJSON.h"
#include "io/resource_manager.hpp"

namespace cJSON_Types
{

Sprite parse_sprite(const cJSON* json, Resource_Manager& res_mgr)
{
	assert(json);
	const char* texture_name = cJSON_GetObjectItem(json, "texture")->valuestring;
	const Sage_Texture texture = res_mgr.get_texture(texture_name);
	Sprite sprite(texture);
	sprite.texture_clip.position.x = cJSON_GetObjectItem(json, "position_x")->valueint;
	sprite.texture_clip.position.y = cJSON_GetObjectItem(json, "position_y")->valueint;
	sprite.texture_clip.size.x = cJSON_GetObjectItem(json, "size_x")->valueint;
	sprite.texture_clip.size.y = cJSON_GetObjectItem(json, "size_y")->valueint;

	return sprite;
}

cJSON* serialise_sprite(const Sprite& sprite)
{
	assert(!sprite.get_texture_path().empty());

	cJSON* json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "texture", cJSON_CreateString(sprite.get_texture_path().data()));
	cJSON_AddItemToObject(json, "position_x", cJSON_CreateNumber(sprite.texture_clip.position.x));
	cJSON_AddItemToObject(json, "position_y", cJSON_CreateNumber(sprite.texture_clip.position.y));
	cJSON_AddItemToObject(json, "size_x", cJSON_CreateNumber(sprite.texture_clip.size.x));
	cJSON_AddItemToObject(json, "size_y", cJSON_CreateNumber(sprite.texture_clip.size.y));

	return json;
}

}

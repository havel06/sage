#include "cjson_types.hpp"
#include "io/resource_manager.hpp"

namespace cJSON_Types
{

Sprite parse_sprite(const cJSON* json, Resource_Manager& res_mgr)
{
	const char* texture_name = cJSON_GetObjectItem(json, "texture")->valuestring;
	const Texture texture = res_mgr.get_texture(texture_name);
	Sprite sprite(texture);
	sprite.texture_clip.position.x = cJSON_GetObjectItem(json, "position_x")->valueint;
	sprite.texture_clip.position.y = cJSON_GetObjectItem(json, "position_y")->valueint;
	sprite.texture_clip.size.x = cJSON_GetObjectItem(json, "size_x")->valueint;
	sprite.texture_clip.size.y = cJSON_GetObjectItem(json, "size_y")->valueint;

	return sprite;
}

}

#include "item_registry_loader.hpp"
#include "cJSON.h"
#include "utils/file.hpp"
#include "graphics/sprite.hpp"
#include "resource_manager.hpp"
#include "item/item_registry.hpp"
#include "utils/log.hpp"

Item_Registry_Loader::Item_Registry_Loader(Resource_Manager& res_mgr) :
	m_resource_manager{res_mgr}
{
}

void Item_Registry_Loader::load(Item_Registry& registry, String project_root)
{
	// Get file
	String project_file_path = project_root;
	project_file_path.append("/items.json");
	String file_content = read_file_to_str(project_file_path.data());

	const cJSON* json = cJSON_Parse(file_content.data());
	const cJSON* items = cJSON_GetObjectItem(json, "items");

	const cJSON* item_json;
	cJSON_ArrayForEach(item_json, items) {
		const String id = cJSON_GetObjectItem(item_json, "id")->valuestring;
		const String name = cJSON_GetObjectItem(item_json, "name")->valuestring;
		const cJSON* sprite_json = cJSON_GetObjectItem(item_json, "sprite");
		Sprite sprite = load_sprite(sprite_json);
		registry.add_item(Item{
			.id = id,
			.name = name,
			.sprite = sprite,
		});
	}

	SG_INFO("Loaded item registry");
}

Sprite Item_Registry_Loader::load_sprite(const cJSON* json) {
	const char* texture_name = cJSON_GetObjectItem(json, "texture")->valuestring;
	const Texture texture = m_resource_manager.get_texture(texture_name);
	Sprite sprite(texture);
	sprite.texture_clip.position.x = cJSON_GetObjectItem(json, "position_x")->valueint;
	sprite.texture_clip.position.y = cJSON_GetObjectItem(json, "position_y")->valueint;
	sprite.texture_clip.size.x = cJSON_GetObjectItem(json, "size_x")->valueint;
	sprite.texture_clip.size.y = cJSON_GetObjectItem(json, "size_y")->valueint;

	return sprite;
}

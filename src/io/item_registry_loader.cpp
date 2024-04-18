#include "item_registry_loader.hpp"
#include "cJSON.h"
#include "utils/file.hpp"
#include "graphics/sprite.hpp"
#include "resource_manager.hpp"
#include "item/item_registry.hpp"
#include "utils/log.hpp"
#include "cjson_types.hpp"

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
		Sprite sprite = cJSON_Types::parse_sprite(sprite_json, m_resource_manager);
		registry.add_item(Item{
			.id = id,
			.name = name,
			.sprite = sprite,
		});
	}

	SG_INFO("Loaded item registry");
}

#include "item_registry_loader.hpp"
#include "utils/file.hpp"
#include "graphics/sprite.hpp"
#include "item/item_registry.hpp"
#include "utils/log.hpp"
#include "utils/json.hpp"
#include "json_types.hpp"

Item_Registry_Loader::Item_Registry_Loader(Texture_Manager& tex_mgr) :
	m_texture_manager{tex_mgr}
{
}

void Item_Registry_Loader::load(Item_Registry& registry, const String& project_root)
{
	// FIXME - error handling
	String filename = project_root;
	filename.append("/items.json");
	JSON::Object json = JSON::Object::from_file(filename.data());
	JSON::Object_View view = json.get_view();

	JSON::Array_View items = view["items"].as_array();

	items.for_each([&](const JSON::Value_View& item) {
		const String id = item.as_object()["id"].as_string();
		const String name = item.as_object()["name"].as_string();
		Sprite sprite = JSON_Types::parse_sprite(item.as_object()["sprite"].as_object(), m_texture_manager);
		registry.add_item(Item{
			.id = id,
			.name = name,
			.sprite = sprite,
		});
	});

	SG_INFO("Loaded item registry");
}

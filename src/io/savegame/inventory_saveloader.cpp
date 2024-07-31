#include "inventory_saveloader.hpp"
#include "item/inventory.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include <assert.h>

JSON::Array Inventory_Saveloader::save(const Inventory& inventory)
{
	JSON::Array json;

	inventory.for_each_entry([&](const String& id, int count){
		json.add(serialise_item_stack(id, count));
	});

	return json;
}

void Inventory_Saveloader::load(Inventory& inventory, const JSON::Array_View& json)
{
	json.for_each([&](const JSON::Value_View& value){
		JSON::Object_View item_stack_json = value.as_object();

		const char* id = item_stack_json["id"].as_string(nullptr);
		if (!id) {
			SG_ERROR("Unable to load inventory item: item id missing.");
			return;
		}

		const int count = item_stack_json["count"].as_int(0);
		inventory.add_item(id, count);
	});
}

JSON::Object Inventory_Saveloader::serialise_item_stack(const String& id, int count)
{
	JSON::Object json;
	json.add("id", JSON::Value{id.data()});
	json.add("count", JSON::Value{count});
	return json;
}

#include "inventory_saveloader.hpp"
#include "item/inventory.hpp"
#include "utils/string.hpp"
#include <cJSON.h>
#include <assert.h>

cJSON* Inventory_Saveloader::save(const Inventory& inventory)
{
	// Create json object
	cJSON* json = cJSON_CreateArray();

	inventory.for_each_entry([&](const String& id, int count){
		cJSON_AddItemToArray(json, serialise_item_stack(id, count));
	});

	return json;
}

void Inventory_Saveloader::load(Inventory& inventory, const cJSON* json)
{
	const cJSON* item_stack_json;
	cJSON_ArrayForEach(item_stack_json, json) {
		const char* id = cJSON_GetObjectItem(item_stack_json, "id")->valuestring;
		const int count = cJSON_GetObjectItem(item_stack_json, "count")->valueint;
		inventory.add_item(id, count);
	}
}

cJSON* Inventory_Saveloader::serialise_item_stack(const String& id, int count)
{
	cJSON* json = cJSON_CreateObject();
	cJSON_AddItemToObject(json, "id", cJSON_CreateString(id.data()));
	cJSON_AddItemToObject(json, "count", cJSON_CreateNumber(count));
	return json;
}

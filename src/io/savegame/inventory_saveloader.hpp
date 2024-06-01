#pragma once

// fwd
struct cJSON;
class Inventory;
class String;

class Inventory_Saveloader
{
public:
	cJSON* save(const Inventory&);
	void load(Inventory&, const cJSON*);
private:
	cJSON* serialise_item_stack(const String& id, int count);
};

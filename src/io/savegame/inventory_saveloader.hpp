#pragma once

// fwd
class Inventory;
class String;
namespace JSON {
	class Array;
	class Object;
	class Array_View;
}

class Inventory_Saveloader
{
public:
	JSON::Array save(const Inventory&);
	void load(Inventory&, const JSON::Array_View&);
private:
	JSON::Object serialise_item_stack(const String& id, int count);
};

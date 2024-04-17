#pragma once

#include "item.hpp"
#include "utils/table.hpp"

class Item_Registry
{
public:
	// NOTE - Reference may get invalidated!
	const Item& get_item(const String& id) const;
	void add_item(Item&&);
private:
	Array<Item> m_items;
};

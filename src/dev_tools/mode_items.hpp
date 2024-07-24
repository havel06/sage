#pragma once

#include "utils/string.hpp"

class Item_Registry;
class Inventory;

class Dev_Tools_Mode_Items
{
public:
	Dev_Tools_Mode_Items(const Item_Registry&, Inventory&);
	void draw();
private:
	const Item_Registry& m_item_registry;
	Inventory& m_inventory;
	String m_selected_item;
};

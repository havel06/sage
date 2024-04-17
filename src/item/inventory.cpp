#include "inventory.hpp"

void Inventory::add_item(const String& id, int count)
{
	if (m_items.contains(id)) {
		*m_items.get(id) += count;
	} else {
		m_items.insert(String{id}, int{count});
	}
}

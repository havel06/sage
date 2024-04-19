#include "inventory.hpp"
#include "utils/log.hpp"

void Inventory::add_item(const String& id, int count)
{
	if (m_items.contains(id)) {
		*m_items.get(id) += count;
	} else {
		m_items.insert(String{id}, int{count});
	}
}

void Inventory::remove_item(const String& id, int count)
{
	if (!m_items.contains(id)) {
		SG_ERROR("Tried to remove %d \"%s\" from inventory, item not present", count, id.data());
		return;
	}

	int& current_count = *m_items.get(id);

	if (current_count < count) {
		SG_ERROR("Tried to remove %d \"%s\" from inventory, insufficient amount", count, id.data());
		current_count = 0;
	} else {
		current_count -= count;
	}
}

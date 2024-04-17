#include "item_registry.hpp"
#include "utils/log.hpp"
#include <cassert>

const Item& Item_Registry::get_item(const String& id)
{
	for (int i = 0; i < m_items.size(); i++) {
		if (m_items[i].id == id) {
			return m_items[i];
		}
	}

	SG_ERROR("Invalid item id %s", id.data());
	assert(false);
}

void Item_Registry::add_item(Item&& item)
{
	m_items.push_back((Item&&)item);
}

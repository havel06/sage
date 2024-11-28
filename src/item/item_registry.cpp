#include "item_registry.hpp"
#include "utils/log.hpp"
#include <assert.h>

bool Item_Registry::item_exists(const String &id) const
{
	for (const Item& item : m_items) {
		if (item.id == id)
			return true;
	}

	return false;
}

const Item& Item_Registry::get_item(const String& id) const
{
	for (int i = 0; i < m_items.size(); i++) {
		if (m_items[i].id == id) {
			return m_items[i];
		}
	}

	SG_ERROR("Invalid item id \"%s\"", id.data());
	assert(false);
}

Item& Item_Registry::get_item(const String& id)
{
	for (int i = 0; i < m_items.size(); i++) {
		if (m_items[i].id == id) {
			return m_items[i];
		}
	}

	SG_ERROR("Invalid item id \"%s\"", id.data());
	assert(false);
}

void Item_Registry::add_item(Item&& item)
{
	m_items.push_back((Item&&)item);
}

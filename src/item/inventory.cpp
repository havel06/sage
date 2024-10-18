#include "inventory.hpp"
#include "utils/log.hpp"

void Inventory::add_item(const String& id, int count)
{
	if (m_items.contains(id)) {
		*m_items.get(id) += count;
	} else {
		m_items.insert(String{id}, int{count});
	}

	notify_observers();
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

	notify_observers();
}

int Inventory::get_item_count(const String& id) const
{
	if (m_items.contains(id)) {
		return *m_items.get(id);
	} else {
		return 0;
	}
}

void Inventory::add_observer(Inventory_Observer& observer) const
{
	m_observers.push_back(&observer);
}

void Inventory::remove_observer(Inventory_Observer& observer) const
{
	for (int i = 0; i < m_observers.size(); i++) {
		if (m_observers[i] == &observer) {
			m_observers.remove(i);
			return;
		}
	}
}

void Inventory::notify_observers()
{
	for (auto* observer : m_observers) {
		observer->on_inventory_change();
	}
}

void Inventory::clear()
{
	m_items.clear();
	notify_observers();
}

bool Inventory::is_empty() const
{
	return m_items.size() == 0;
}

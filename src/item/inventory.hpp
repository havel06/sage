#pragma once
#include "utils/string.hpp"
#include "utils/table.hpp"

class Inventory
{
public:
	void add_item(const String& id, int count);
	void remove_item(const String& id, int count);
	int get_item_count(const String& id) const;

	// Callable takes two parameters:
	// - const String& id
	// - int count
	template<typename Callable>
	void for_each_entry(Callable) const;
private:
	// Maps id to count
	Table<String, int> m_items;
};



// Implementation

template<typename Callable>
void Inventory::for_each_entry(Callable c) const
{
	m_items.for_each(c);
}

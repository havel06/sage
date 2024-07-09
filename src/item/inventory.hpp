#pragma once
#include "utils/string.hpp"
#include "utils/table.hpp"
#include "utils/concepts.hpp"

class Inventory_Observer
{
public:
	virtual void on_inventory_change() = 0;
};


class Inventory
{
public:
	void add_item(const String& id, int count);
	void remove_item(const String& id, int count);
	int get_item_count(const String& id) const;

	void add_observer(Inventory_Observer&) const;
	void remove_observer(Inventory_Observer&) const;

	// Callable takes two parameters:
	// - const String& id
	// - int count
	template<typename Fn>
	requires Concepts::Callable<Fn, const String&, int>
	void for_each_entry(Fn) const;
private:
	void notify_observers();

	// Maps id to count
	Table<String, int> m_items;
	mutable Array<Inventory_Observer*> m_observers;
};



// Implementation

template<typename Fn>
requires Concepts::Callable<Fn, const String&, int>
void Inventory::for_each_entry(Fn c) const
{
	m_items.for_each(c);
}

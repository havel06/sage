#pragma once

#include "item.hpp"
#include "utils/concepts.hpp"
#include "utils/array.hpp"

class Item_Registry
{
public:
	// NOTE - Reference may get invalidated!
	const Item& get_item(const String& id) const;
	Item& get_item(const String& id);
	bool item_exists(const String& id) const;

	void add_item(Item&&);

	template<typename Fn>
	requires Concepts::Callable<Fn, const Item&>
	void for_each(Fn) const;
private:
	Array<Item> m_items;
};


// Implementation
template<typename Fn>
requires Concepts::Callable<Fn, const Item&>
void Item_Registry::for_each(Fn fn) const
{
	for (const Item& item : m_items) {
		fn(item);
	}
}

#pragma once

#include "pool.hpp"

// A simple non-ordered key-value table, using a pool on the background
template<typename Key, typename T, int Size>
class Pool_Table
{
public:
	T& insert(Key&&, T&&);
	void clear();

	T* get(const Key&);
	const T* get(const Key&) const;
	bool contains(const Key&) const;
	template<typename Callable>
	void for_each(Callable c);

private:
	struct Item
	{
		Key key;
		T value;
	};

	Pool<Item, Size> m_data;
};

// Implementation

template<typename Key, typename T, int Size>
T& Pool_Table<Key, T, Size>::insert(Key&& key, T&& value)
{
	assert(!contains(key));
	int index = m_data.add(Item{(Key&&)key, (T&&)value});
	return m_data.get(index)->value;
}

template<typename Key, typename T, int Size>
void Pool_Table<Key, T, Size>::clear()
{
	m_data.clear();
}

template<typename Key, typename T, int Size>
T* Pool_Table<Key, T, Size>::get(const Key& key)
{
	T* result = nullptr;

	m_data.for_each_active([&](int, Item& item)
	{
		if (item.key == key)
			result = &item.value;
	});

	return result;
}

template<typename Key, typename T, int Size>
const T* Pool_Table<Key, T, Size>::get(const Key& key) const
{
	const T* result = nullptr;

	m_data.for_each_active([&](int, const Item& item)
	{
		if (item.key == key)
			result = &item.value;
	});

	return result;
}

template<typename Key, typename T, int Size>
bool Pool_Table<Key, T, Size>::contains(const Key& key) const
{
	return get(key) != nullptr;
}

template<typename Key, typename T, int Size>
template<typename Callable>
void Pool_Table<Key, T, Size>::for_each(Callable c)
{
	for (int i = 0; i < m_data.size(); i++)
	{
		c(m_data[i].value);
	}
}


#pragma once

#include "array.hpp"
#include "concepts.hpp"
#include "optional.hpp"

// A simple non-ordered key-value table
template<typename Key, typename T>
class Table
{
public:
	T& insert(Key&&, T&&);
	void remove(const Key&);
	void clear();
	int size() const { return m_data.size(); }

	T* get(const Key&);
	const T* get(const Key&) const;
	Optional<T> get_opt(const Key&) const;
	bool contains(const Key&) const;

	template<typename Fn>
	requires Concepts::Callable<Fn, const Key&, T&>
	void for_each(Fn c);

	template<typename Fn>
	requires Concepts::Callable<Fn, const Key&, const T&>
	void for_each(Fn c) const;

private:
	struct Item
	{
		Key key;
		T value;
	};

	Array<Item> m_data;
};

// Implementation

template<typename Key, typename T>
T& Table<Key, T>::insert(Key&& key, T&& value)
{
	assert(!contains(key));
	m_data.push_back(Item{(Key&&)key, (T&&)value});
	return m_data.back().value;
}

template<typename Key, typename T>
void Table<Key, T>::remove(const Key& key)
{
	for (int i = 0; i < m_data.size(); i++) {
		const Item& item = m_data[i];
		if (item.key == key) {
			m_data.remove(i);
			return;
		}
	}
}

template<typename Key, typename T>
void Table<Key, T>::clear()
{
	m_data.clear();
}

template<typename Key, typename T>
T* Table<Key, T>::get(const Key& key)
{
	for (int i = 0; i < m_data.size(); i++)
	{
		if (m_data[i].key == key)
		{
			return &m_data[i].value;
		}
	}

	return nullptr;
}

template<typename Key, typename T>
const T* Table<Key, T>::get(const Key& key) const
{
	for (int i = 0; i < m_data.size(); i++)
	{
		if (m_data[i].key == key)
		{
			return &m_data[i].value;
		}
	}

	return nullptr;
}

template<typename Key, typename T>
Optional<T> Table<Key, T>::get_opt(const Key& key) const
{
	const T* ptr = get(key);
	if (ptr) {
		return Optional<T>{*ptr};
	} else {
		return Optional<T>{};
	}
}

template<typename Key, typename T>
bool Table<Key, T>::contains(const Key& key) const
{
	return get(key) != nullptr;
}

template<typename Key, typename T>
template<typename Fn>
requires Concepts::Callable<Fn, const Key&, T&>
void Table<Key, T>::for_each(Fn c)
{
	for (int i = 0; i < m_data.size(); i++)
	{
		c(m_data[i].key, m_data[i].value);
	}
}

template<typename Key, typename T>
template<typename Fn>
requires Concepts::Callable<Fn, const Key&, const T&>
void Table<Key, T>::for_each(Fn c) const
{
	for (int i = 0; i < m_data.size(); i++)
	{
		c(m_data[i].key, m_data[i].value);
	}
}

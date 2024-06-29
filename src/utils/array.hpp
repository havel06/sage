#pragma once
#include <new>
#include <assert.h>
#include <stdlib.h>

// fwd
template<typename T>
class Array;


template<typename T>
class Array_Iterator
{
public:	
	Array_Iterator(Array<T>& a, int index) :
		m_array{a},
		m_index{index}
	{
	}

	Array_Iterator& operator++() {
		m_index++;
		return *this;
	}

	T& operator*() {
		return m_array[m_index];
	}

	bool operator==(const Array_Iterator& other) const {
		return (&m_array == &other.m_array && m_index == other.m_index);
	}
private:
	Array<T>& m_array;
	int m_index = 0;
};

template<typename T>
class Array_Const_Iterator
{
public:	
	Array_Const_Iterator(const Array<T>& a, int index) :
		m_array{a},
		m_index{index}
	{
	}

	Array_Const_Iterator& operator++() {
		m_index++;
		return *this;
	}

	T& operator*() {
		return m_array[m_index];
	}

	bool operator==(const Array_Const_Iterator& other) const {
		return (&m_array == &other.m_array && m_index == other.m_index);
	}
private:
	const Array<T>& m_array;
	int m_index = 0;
};


template<typename T>
class Array
{
public:
	Array() = default;
	Array(const Array& other);
	Array(Array&& other);
	Array& operator=(const Array& other);
	Array& operator=(Array&& other); // FIXME - implement
	~Array();

	const T* data() const;
	T* data();
	T& back();

	void clear();
	void push_back(T&&);
	void push_back(const T&);
	void resize(int size, const T& value = T{});
	void pop_back();
	void remove(int index);

	void reserve(int size);
	int size() const;
	bool empty() const;
	bool contains(const T& value) const;

	const T& operator[](int i) const;
	T& operator[](int i);

	Array_Iterator<T> begin();
	Array_Iterator<T> end();
	Array_Const_Iterator<T> begin() const;
	Array_Const_Iterator<T> end() const;
private:
	T* m_data = nullptr;
	int m_size = 0;
	int m_capacity = 0;
};


// Implementation

template<typename T>
Array<T>::~Array()
{
	clear();
	if (m_data)
		free(m_data);
}

template<typename T>
Array<T>::Array(const Array& other)
{
	if (other.size() == 0)
		return;

	reserve(other.size());
	for (int i = 0; i < other.size(); i++)
	{
		push_back(other[i]);
	}
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	clear();

	if (other.size() == 0)
		return *this;

	reserve(other.size());
	for (int i = 0; i < other.size(); i++)
	{
		push_back(other[i]);
	}

	return *this;
}

template<typename T>
Array<T>::Array(Array&& other)
{
	m_data = other.m_data;
	other.m_data = nullptr;

	m_size = other.m_size;
	other.m_size = 0;

	m_capacity = other.m_capacity;
	other.m_capacity = 0;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& other)
{
	clear();
	if (m_data)
		free(m_data);

	m_data = other.m_data;
	other.m_data = nullptr;

	m_size = other.m_size;
	other.m_size = 0;

	m_capacity = other.m_capacity;
	other.m_capacity = 0;

	return *this;
}

template<typename T>
void Array<T>::clear()
{
	for (int i = 0; i < m_size; i++)
	{
		(m_data[i]).~T();
	}

	m_size = 0;
}

template<typename T>
void Array<T>::push_back(T&& element)
{
	if (m_size == m_capacity)
	{
		reserve(m_capacity == 0 ? 1 : m_capacity * 2);
	}

	new (&(m_data[m_size++])) T((T&&)element);
}

template<typename T>
void Array<T>::push_back(const T& element)
{
	push_back(T{element});
}

template<typename T>
void Array<T>::reserve(int size)
{
	assert(size > 0);

	if (m_capacity >= size)
		return;

	T* new_data = (T*)malloc(sizeof(T) * size);

	// move old elements
	for (int i = 0; i < m_size; i++)
	{
		new (&new_data[i]) T((T&&)(m_data[i]));
		m_data[i].~T();
	}

	free(m_data);
	m_data = new_data;
	m_capacity = size;
}

template<typename T>
int Array<T>::size() const
{
	return m_size;
}

template<typename T>
const T& Array<T>::operator[](int i) const
{
	assert(i < m_size);
	assert(i >= 0);

	return m_data[i];
}

template<typename T>
T& Array<T>::operator[](int i)
{
	assert(i < m_size);
	assert(i >= 0);

	return m_data[i];
}

template<typename T>
const T* Array<T>::data() const
{
	return m_data;
}

template<typename T>
T* Array<T>::data()
{
	return m_data;
}

template<typename T>
T& Array<T>::back()
{
	assert(m_size > 0);
	return m_data[m_size - 1];
}

template<typename T>
bool Array<T>::empty() const
{
	return m_size == 0;
}

template<typename T>
void Array<T>::resize(int size, const T& value)
{
	assert(size > 0);

	reserve(size);
	for (int i = 0; i < size; i++)
	{
		push_back(value);
	}
}

template<typename T>
void Array<T>::pop_back()
{
	assert(!empty());

	m_data[m_size - 1].~T();
	m_size--;
}

template<typename T>
bool Array<T>::contains(const T& value) const
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_data[i] == value)
			return true;
	}
	return false;
}

template<typename T>
void Array<T>::remove(int index)
{
	assert(index >= 0);
	assert(index < m_size);
	
	for (int i = index; i < m_size - 1; i++)
	{
		m_data[i] = (T&&)(m_data[i + 1]);
	}

	m_size--;
	m_data[m_size].~T();
}

template<typename T>
Array_Iterator<T> Array<T>::begin()
{
	return Array_Iterator<T>(*this, 0);
}

template<typename T>
Array_Iterator<T> Array<T>::end()
{
	return Array_Iterator<T>(*this, m_size);
}

template<typename T>
Array_Const_Iterator<T> Array<T>::begin() const
{
	return Array_Const_Iterator<T>(*this, 0);
}

template<typename T>
Array_Const_Iterator<T> Array<T>::end() const
{
	return Array_Const_Iterator<T>(*this, m_size);
}

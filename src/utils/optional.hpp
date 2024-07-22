#pragma once

#include <string.h>
#include <assert.h>
#include <new>

template<typename T>
class Optional
{
public:
	Optional() = default;
	Optional(const T&);
	Optional(T&&);
	Optional(Optional&& other);
	Optional(const Optional& other);
	Optional& operator=(Optional&& other);
	Optional& operator=(const Optional& other);
	~Optional();

	T& value();
	const T& value() const;
	bool has_value() const;
	void clear();

private:
	void emplace(const T&);
	void emplace(T&&);

	bool m_has_value = false;
	alignas(T) unsigned char m_value[sizeof(T)];
};


// Implementation
//
template<typename T>
Optional<T>::Optional(const T& init)
{
	this->emplace(init);
}

template<typename T>
Optional<T>::Optional(T&& init)
{
	this->emplace((T&&)init);
}

template<typename T>
Optional<T>::~Optional()
{
	clear();
}

template<typename T>
Optional<T>::Optional(Optional&& other)
{
	if (other.has_value()) {
		emplace((T&&)other.value());
	}

	other.clear();
}

template<typename T>
Optional<T>::Optional(const Optional& other)
{
	if (other.has_value()) {
		emplace(other.value());
	}
}

template<typename T>
Optional<T>& Optional<T>::operator=(Optional&& other)
{
	clear();
	
	if (other.has_value()) {
		emplace((T&&)other.value());
	}

	other.clear();

	return *this;
}

template<typename T>
Optional<T>& Optional<T>::operator=(const Optional& other)
{
	clear();

	if (other.has_value()) {
		emplace(other.value());
	}

	return *this;
}

template<typename T>
void Optional<T>::clear()
{
	if (m_has_value) {
		value().~T();
		m_has_value = false;
	}
}

template<typename T>
bool Optional<T>::has_value() const
{
	return m_has_value;
}

template<typename T>
void Optional<T>::emplace(const T& val)
{
	clear();

	if (m_has_value) {
		value() = val;
	} else {
		new (m_value) T (val);
	}

	m_has_value = true;
}

template<typename T>
void Optional<T>::emplace(T&& val)
{
	clear();

	if (m_has_value) {
		value() = (T&&)val;
	} else {
		new (m_value) T ((T&&)val);
	}

	m_has_value = true;
}

template<typename T>
T& Optional<T>::value()
{
	assert(m_has_value);
	return *((T*)m_value);
}

template<typename T>
const T& Optional<T>::value() const
{
	assert(m_has_value);
	return *((T*)m_value);
}


#pragma once

#include "utils/move.hpp"

template <typename Resource_Type>
class Resource
{
public:
	Resource(Resource_Type&&);
	const Resource_Type& get() const;
	Resource_Type& get();

	// FIXME - use passkey idiom to only allow handle to ref and unref?
	void reference(); // Add to reference count
	void unreference(); // Subtract from reference count
	int get_reference_count() const;
private:
	int m_reference_count = 0;
	Resource_Type m_data;
};



// IMPLEMENTATION

template <typename Resource_Type>
Resource<Resource_Type>::Resource(Resource_Type&& res) :
	m_data{move(res)}
{
}

template <typename Resource_Type>
const Resource_Type& Resource<Resource_Type>::get() const
{
	return m_data;
}

template <typename Resource_Type>
Resource_Type& Resource<Resource_Type>::get()
{
	return m_data;
}

template <typename Resource_Type>
void Resource<Resource_Type>::reference()
{
	m_reference_count++;
}

template <typename Resource_Type>
void Resource<Resource_Type>::unreference()
{
	m_reference_count--;
}

template <typename Resource_Type>
int Resource<Resource_Type>::get_reference_count() const
{
	return m_reference_count;
}

#pragma once

#include "utils/move.hpp"

template <typename Resource_Type>
class Resource
{
public:
	Resource(Resource_Type&&);
	const Resource_Type& get() const;
	Resource_Type& get();
private:
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

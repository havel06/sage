#pragma once

#include "resource.hpp"

template<typename Resource_Type>
class Resource_Handle
{
public:
	Resource_Handle<Resource_Type>(Resource<Resource_Type>&);
	const Resource_Type& get() const;
	Resource_Type& get();
private:
	Resource<Resource_Type>* m_resource;
};


// IMPLEMENTATION

template<typename Resource_Type>
Resource_Handle<Resource_Type>::Resource_Handle(Resource<Resource_Type>& res)
{
	m_resource = &res;
}

template<typename Resource_Type>
const Resource_Type& Resource_Handle<Resource_Type>::get() const
{
	return m_resource->get();
}

template<typename Resource_Type>
Resource_Type& Resource_Handle<Resource_Type>::get()
{
	return m_resource->get();
}

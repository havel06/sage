#pragma once

#include "resource.hpp"

template<typename Resource_Type>
class Resource_Handle
{
public:
	Resource_Handle(Resource<Resource_Type>&);

	Resource_Handle() = delete;
	Resource_Handle(const Resource_Handle&);
	Resource_Handle(Resource_Handle&&);
	Resource_Handle& operator=(const Resource_Handle&);
	Resource_Handle& operator=(Resource_Handle&&);

	~Resource_Handle();

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
	m_resource->reference();
}

template<typename Resource_Type>
Resource_Handle<Resource_Type>::Resource_Handle(const Resource_Handle& other)
{
	m_resource = other.m_resource;
	m_resource->reference();
}

template<typename Resource_Type>
Resource_Handle<Resource_Type>::Resource_Handle(Resource_Handle&& other)
{
	// Works the same as copy constructor
	m_resource = other.m_resource;
	m_resource->reference();
}

template<typename Resource_Type>
Resource_Handle<Resource_Type>& Resource_Handle<Resource_Type>::operator=(const Resource_Handle& other)
{
	m_resource->unreference();
	m_resource = other.m_resource;
	m_resource->reference();
	return *this;
}

template<typename Resource_Type>
Resource_Handle<Resource_Type>& Resource_Handle<Resource_Type>::operator=(Resource_Handle&& other)
{
	// Works the same as copy assignment
	*this = other;
	return *this;
}

template<typename Resource_Type>
Resource_Handle<Resource_Type>::~Resource_Handle()
{
	m_resource->unreference();
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

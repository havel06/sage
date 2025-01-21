#pragma once
#include "resource_handle.hpp"
#include "resource_manager.hpp"

template<typename Resource_Type>
Resource_Handle<Resource_Type>::Resource_Handle(int id, Resource_Manager<Resource_Type>& mgr) :
	m_manager{mgr}
{
	m_id = id;
	ref();
}

template<typename Resource_Type>
Resource_Handle<Resource_Type>::Resource_Handle(const Resource_Handle& other) :
	m_manager{other.m_manager}
{
	m_id = other.m_id;
	ref();
}

template<typename Resource_Type>
Resource_Handle<Resource_Type>::Resource_Handle(Resource_Handle&& other) :
	m_manager{other.m_manager}
{
	// Works the same as copy constructor
	m_id = other.m_id;
	ref();
}

template<typename Resource_Type>
Resource_Handle<Resource_Type>& Resource_Handle<Resource_Type>::operator=(const Resource_Handle& other)
{
	unref();
	m_id = other.m_id;
	ref();
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
	//SG_DEBUG("destroying resource");
	unref();
}

template<typename Resource_Type>
const Resource_Type& Resource_Handle<Resource_Type>::get() const
{
	Resource<Resource_Type>* ptr = m_manager.get_by_id(m_id);
	assert(ptr);
	return ptr->get();
}

template<typename Resource_Type>
Resource_Type& Resource_Handle<Resource_Type>::get()
{
	Resource<Resource_Type>* ptr = m_manager.get_by_id(m_id);
	assert(ptr);
	return ptr->get();
}

template<typename Resource_Type>
const String& Resource_Handle<Resource_Type>::get_path() const
{
	Resource<Resource_Type>* ptr = m_manager.get_by_id(m_id);
	assert(ptr);
	return ptr->get_path();
}

template<typename Resource_Type>
void Resource_Handle<Resource_Type>::ref()
{
	Resource<Resource_Type>* res = m_manager.get_by_id(m_id);
	assert(res);
	res->reference(Passkey<Self>{});
}

template<typename Resource_Type>
void Resource_Handle<Resource_Type>::unref()
{
	Resource<Resource_Type>* res = m_manager.get_by_id(m_id);

	// During program shutdown, the resource may get destroyed sooner than the handle,
	// since resources can hold handles to other resources.
	if (res)
		res->unreference(Passkey<Self>{});
}

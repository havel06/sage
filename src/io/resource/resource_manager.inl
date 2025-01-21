#pragma once

#include "resource_manager.hpp"

template<typename Resource_Type>
Resource_Manager<Resource_Type>::Resource_Manager(const String& resource_root_path)
{
	m_resource_root_path = resource_root_path;
}

template<typename Resource_Type>
void Resource_Manager<Resource_Type>::unload_free_resources()
{
	Array<int> should_remove{};

	m_resources.for_each([&](const int& id, Resource_Ptr& resource){
		if (resource->get_reference_count() == 0 && can_unload_resource(resource->get())) {
			unload_resource(resource->get(), resource->get_path());
			should_remove.push_back(id);
		}
	});

	for (const int id : should_remove) {
		Resource_Ptr& ptr = *m_resources.get(id);
		String name = ptr->get_path();
		m_resources.remove(id);
		SG_INFO("Unloaded resource \"%s\".", name.data());
	}
}

template<typename Resource_Type>
Resource_Handle<Resource_Type> Resource_Manager<Resource_Type>::get(const String& path, bool absolute_path)
{
	String full_filename = absolute_path ? get_canonical_path(path) : get_full_resource_path(path);

	// Find in cache
	int found_id;
	Resource_Ptr* found_res = nullptr;
	m_resources.for_each([&](const int& id, Resource_Ptr& resource){
		if (resource->get_path() == full_filename) {
			found_id = id;
			found_res = &resource;
		}
	});

	if (found_res) {
		return Resource_Handle<Resource_Type>(found_id, *this);
	} else {
		int new_id = ++m_last_used_id;
		m_resources.insert(int{new_id}, load_resource(full_filename));
		SG_INFO("Loaded resource \"%s\".", full_filename.data());
		return Resource_Handle<Resource_Type>(new_id, *this);
	}
}

template<typename Resource_Type>
Resource<Resource_Type>* Resource_Manager<Resource_Type>::get_by_id(int id)
{
	Resource_Ptr* found = m_resources.get(id);

	if (found) {
		Resource_Ptr& ptr = *found;
		Resource<Resource_Type>& res = *ptr;
		return &res;
	} else {
		return nullptr;
	}
}

template<typename Resource_Type>
Resource_Handle<Resource_Type> Resource_Manager<Resource_Type>::add_internal_resource(Resource_Ptr&& res)
{
	int new_id = ++m_last_used_id;
	m_resources.insert(int{new_id}, move(res));
	return Resource_Handle<Resource_Type>(new_id, *this);
}

template<typename Resource_Type>
String Resource_Manager<Resource_Type>::get_full_resource_path(const String& relative_filename)
{
	String full_filename = m_resource_root_path;
	full_filename.append("/");
	full_filename.append(relative_filename);
	return get_canonical_path(full_filename);
}

template<typename Resource_Type>
template<typename Fn>
requires Concepts::Callable<Fn, Resource<Resource_Type>&>
void Resource_Manager<Resource_Type>::for_each_resource(Fn c)
{
	m_resources.for_each([&](const auto& key, Resource_Ptr& value){
		(void)key;
		Resource<Resource_Type>& res = *value;
		c(res);
	});
}

template<typename Resource_Type>
template<typename Fn>
requires Concepts::Callable<Fn, const String&, Resource_Type&>
void Resource_Manager<Resource_Type>::for_each(Fn c)
{
	for_each_resource([&](Resource<Resource_Type>& res){
		c(res.get_path(), res.get());
	});
}

#pragma once

#include "utils/own_ptr.hpp"
#include "utils/filesystem.hpp"
#include "utils/table.hpp"
#include "utils/concepts.hpp"
#include "utils/log.hpp"
#include "resource.hpp"
#include "resource_handle.hpp"

template<typename Resource_Type>
class Resource_Manager
{
public:
	Resource_Manager(const String& resource_root_path);
	Resource_Handle<Resource_Type> get(const String& file_path, bool absolute_path);
	void unload_free_resources();
protected:
	// Callback must take in one argument, Resource_Type&
	template<typename Fn>
	requires Concepts::Callable<Fn, Resource_Type&>
	void for_each_resource(Fn c);
private:
	using Resource_Ptr = Own_Ptr<Resource<Resource_Type>>;
	String get_full_resource_path(const String& relative_filename);

	virtual Resource_Ptr load_resource(const String& path) = 0;
	virtual void unload_resource(Resource_Type&) = 0;
	virtual bool can_unload_resource(const Resource_Type&) const = 0;

	String m_resource_root_path;
	Table<String, Resource_Ptr> m_resources;
};



// Implementation
template<typename Resource_Type>
Resource_Manager<Resource_Type>::Resource_Manager(const String& resource_root_path)
{
	m_resource_root_path = resource_root_path;
}

template<typename Resource_Type>
void Resource_Manager<Resource_Type>::unload_free_resources()
{
	Array<String> should_remove{};

	m_resources.for_each([&](const String& name, Resource_Ptr& resource){
		if (resource->get_reference_count() == 0 && can_unload_resource(resource->get())) {
			unload_resource(resource->get());
			should_remove.push_back(name);
		}
	});

	for (const String& name : should_remove) {
		m_resources.remove(name);
		SG_INFO("Unloaded resource \"%s\".", name.data());
	}
}

template<typename Resource_Type>
Resource_Handle<Resource_Type> Resource_Manager<Resource_Type>::get(const String& path, bool absolute_path)
{
	String full_filename = absolute_path ? get_canonical_path(path) : get_full_resource_path(path);

	// Find in cache
	Resource_Ptr* found = m_resources.get(full_filename);
	if (found) {
		return Resource_Handle<Resource_Type>(**found);
	} else {
		Resource_Ptr& res = m_resources.insert(String{full_filename}, load_resource(full_filename));
		SG_INFO("Loaded resource \"%s\".", full_filename.data());
		return Resource_Handle<Resource_Type>(*res);
	}
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
requires Concepts::Callable<Fn, Resource_Type&>
void Resource_Manager<Resource_Type>::for_each_resource(Fn c)
{
	m_resources.for_each([&](const auto& key, Resource_Ptr& value){
		(void)key;
		Resource<Resource_Type>& res = *value;
		c(res.get());
	});
}

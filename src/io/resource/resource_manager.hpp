#pragma once

#include "utils/own_ptr.hpp"
#include "utils/filesystem.hpp"
#include "utils/table.hpp"
#include "utils/concepts.hpp"
#include "utils/log.hpp"
#include "resource.hpp"
#include "resource_handle.hpp"

// To use the template, include resource_manager.inl
template<typename Resource_Type>
class Resource_Manager
{
public:
	Resource_Manager(const String& resource_root_path);
	Resource_Handle<Resource_Type> get(const String& file_path, bool absolute_path);
	void unload_free_resources();

	// Callable must take two arguments, const String& (path) and Sequence&
	template<typename Fn>
	requires Concepts::Callable<Fn, const String&, Resource_Type&>
	void for_each(Fn c);

	// API for Resource_Handle
	Resource<Resource_Type>* get_by_id(int id);
protected:
	using Resource_Ptr = Own_Ptr<Resource<Resource_Type>>;

	// Callback must take in one argument, Resource<Resource_Type>&
	template<typename Fn>
	requires Concepts::Callable<Fn, Resource<Resource_Type>&>
	void for_each_resource(Fn c);

	// Adds a resource that is not loaded from a file.
	Resource_Handle<Resource_Type> add_internal_resource(Resource_Ptr&&);
private:
	String get_full_resource_path(const String& relative_filename);

	virtual Resource_Ptr load_resource(const String& path) = 0;
	virtual void unload_resource(Resource_Type&, const String& path) = 0;
	virtual bool can_unload_resource(const Resource_Type&) const = 0;

	String m_resource_root_path;
	int m_last_used_id = 0;
	Table<int /*id*/, Resource_Ptr> m_resources;
};

#include "resource_manager.inl"

#pragma once

#include "resource.hpp"
#include "utils/log.hpp"

// fwd
template<typename Resource_Type>
class Resource_Manager;

template<typename Resource_Type>
class Resource_Handle
{
public:
	using Self = Resource_Handle<Resource_Type>;

	Resource_Handle(int id, Resource_Manager<Resource_Type>&);

	Resource_Handle() = delete;
	Resource_Handle(const Resource_Handle&);
	Resource_Handle(Resource_Handle&&);
	Resource_Handle& operator=(const Resource_Handle&);
	Resource_Handle& operator=(Resource_Handle&&);

	~Resource_Handle();

	const Resource_Type& get() const;
	Resource_Type& get();
	const String& get_path() const;
private:
	void ref();
	void unref();

	int m_id;
	Resource_Manager<Resource_Type>& m_manager;
};

#include "resource_handle.inl"

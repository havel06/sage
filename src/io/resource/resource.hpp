#pragma once

#include "utils/move.hpp"
#include "utils/string.hpp"
#include "utils/passkey.hpp"

// fwd
template<typename Resource_Type>
class Resource_Handle;

template <typename Resource_Type>
class Resource
{
public:
	using Handle = Resource_Handle<Resource_Type>;

	Resource(const String& path, Resource_Type&&);
	const String& get_path() const { return m_path; }
	const Resource_Type& get() const;
	Resource_Type& get();

	void reference(Passkey<Handle>); // Add to reference count
	void unreference(Passkey<Handle>); // Subtract from reference count
	int get_reference_count() const;
private:
	int m_reference_count = 0;
	String m_path;
	Resource_Type m_data;
};



// IMPLEMENTATION

template <typename Resource_Type>
Resource<Resource_Type>::Resource(const String& path, Resource_Type&& res) :
	m_path{move(path)},
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
void Resource<Resource_Type>::reference(Passkey<Handle>)
{
	m_reference_count++;
}

template <typename Resource_Type>
void Resource<Resource_Type>::unreference(Passkey<Handle>)
{
	m_reference_count--;
}

template <typename Resource_Type>
int Resource<Resource_Type>::get_reference_count() const
{
	return m_reference_count;
}

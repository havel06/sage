#pragma once

#include "utils/string.hpp"
#include "utils/concepts.hpp"
#include <cJSON.h>

namespace JSON
{

// fwd
class Object_View;
class Array_View;
class Array;
class Object;

class Value_View
{
public:
	Value_View(const cJSON*);

	int as_int(int fallback_value) const;
	bool as_bool(bool fallback_value) const;
	float as_float(float fallback_value) const;
	const char* as_string(const char* fallback_value) const;

	// FIXME - Return empty array on error
	Array_View as_array() const;
	// FIXME - Return empty object on error
	Object_View as_object() const;

	bool is_null() const;
	bool is_string() const;
private:
	const cJSON* m_cjson;
};



class Object_View
{
public:
	Object_View(const cJSON*);
	bool has(const char* key) const;
	Value_View get(const char* key) const;
	Value_View operator[](const char* key) const { return get(key); }
private:
	const cJSON* m_cjson;
};



class Array_View
{
public:
	Array_View(const cJSON*);

	template<typename Fn>
	requires Concepts::Callable<Fn, const Value_View&>
	void for_each(Fn callback) const;
private:
	const cJSON* m_cjson;
};

class Value
{
public:
	Value(int);
	Value(float);
	Value(bool);
	Value(const char*);
	Value(Array&&);
	Value(Object&&);
	~Value();

	cJSON* release() &&;
	Value_View get_view() const;
private:
	Value(cJSON*);

	cJSON* m_cjson;
};

class Array
{
public:
	Array();
	~Array();

	Array(Array&& other);
	Array(const Array& other) = delete;

	void add(JSON::Value&&);

	cJSON* release() &&;
	Array_View get_view() const;
private:
	cJSON* m_cjson;
};

class Object
{
public:
	Object();
	~Object();
	static Object from_file(const char* filename);
	void write_to_file(const char* filename);

	Object(Object&&);
	// TODO - implement?
	Object(const Object&) = delete;
	Object& operator=(const Object&) = delete;
	Object& operator=(Object&&) = delete;

	void add(const char* key, Value&&);

	Object_View get_view() const;
	cJSON* release() &&;
private:
	Object(cJSON*);

	cJSON* m_cjson;
};



// Implementation

template<typename Fn>
requires Concepts::Callable<Fn, const Value_View&>
void Array_View::for_each(Fn callback) const
{
	const cJSON* item = nullptr;
	cJSON_ArrayForEach(item, m_cjson) {
		callback(Value_View{item});
	}
}


}

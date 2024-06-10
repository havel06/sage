#pragma once

#include "utils/string.hpp"
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

	int as_int() const;
	bool as_bool() const;
	float as_float() const;
	const char* as_string() const;
	Array_View as_array() const;
	Object_View as_object() const;
	bool is_null() const;
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

	// Callable should take one argument, const Value_View&
	template<typename Callable>
	void for_each(Callable callback) const;
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

template<typename Callable>
void Array_View::for_each(Callable callback) const
{
	const cJSON* item = nullptr;
	cJSON_ArrayForEach(item, m_cjson) {
		callback(Value_View{item});
	}
}


}

#pragma once

#include "utils/string.hpp"
#include <cJSON.h>

namespace JSON
{

// fwd
class Object_View;
class Array_View;

class Value_View
{
public:
	Value_View(const cJSON*);
	int as_int() const;
	float as_float() const;
	const char* as_string() const;
	Array_View as_array() const;
	Object_View as_object() const;
private:
	const cJSON* m_cjson;
};



class Object_View
{
public:
	Object_View(const cJSON*);
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
	void for_each(Callable callback);
private:
	const cJSON* m_cjson;
};



// Implementation

template<typename Callable>
void Array_View::for_each(Callable callback)
{
	const cJSON* item = nullptr;
	cJSON_ArrayForEach(item, m_cjson) {
		callback(Value_View{item});
	}
}


}

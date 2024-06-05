#include "json.hpp"
#include "utils/array.hpp"
#include <cJSON.h>


namespace JSON
{


Value_View::Value_View(const cJSON* cjson)
{
	assert(cjson);
	m_cjson = cjson;
}

int Value_View::as_int() const
{
	assert(cJSON_IsNumber(m_cjson));
	return m_cjson->valueint;
}

float Value_View::as_float() const
{
	assert(cJSON_IsNumber(m_cjson));
	return m_cjson->valuedouble;
}

const char* Value_View::as_string() const
{
	assert(cJSON_IsString(m_cjson));
	return m_cjson->valuestring;
}

Array_View Value_View::as_array() const
{
	assert(cJSON_IsArray(m_cjson));
	return Array_View(m_cjson);
}

Object_View Value_View::as_object() const
{
	assert(cJSON_IsObject(m_cjson));
	return Object_View(m_cjson);
}

Object_View::Object_View(const cJSON* cjson)
{
	assert(cjson);
	assert(cJSON_IsObject(cjson));
}

Value_View Object_View::get(const char* key) const
{
	return Value_View(cJSON_GetObjectItem(m_cjson, key));
}

Array_View::Array_View(const cJSON* cjson)
{
	assert(cjson);
	assert(cJSON_IsArray(cjson));
	m_cjson = cjson;
}


}

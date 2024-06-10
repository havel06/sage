#include "json.hpp"
#include "utils/array.hpp"
#include "utils/file.hpp"
#include <cJSON.h>
#include "utils/log.hpp"
#include <stdio.h>

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

bool Value_View::as_bool() const
{
	assert(cJSON_IsBool(m_cjson));
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

bool Value_View::is_null() const
{
	return m_cjson && cJSON_IsNull(m_cjson);
}

Object_View::Object_View(const cJSON* cjson)
{
	assert(cjson);
	assert(cJSON_IsObject(cjson));
	m_cjson = cjson;
}

bool Object_View::has(const char* key) const
{
	return cJSON_HasObjectItem(m_cjson, key);
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

Object::~Object()
{
	delete m_cjson;
}

Object::Object()
{
	m_cjson = cJSON_CreateObject();
}

Object::Object(cJSON* cjson)
{
	m_cjson = cjson;
}

Object_View Object::get_view() const
{
	return Object_View{m_cjson};
}

Object Object::from_file(const char* filename)
{
	String file_content = read_file_to_str(filename);
	cJSON* cjson = cJSON_Parse(file_content.data());

	if (!cjson) {
		SG_ERROR("Error when parsing JSON file \"%s\"", filename);
	}

	return Object{cjson};
}

void Object::write_to_file(const char* filename)
{
	FILE* f = fopen(filename, "w");
	assert(f);
	char* json_str = cJSON_Print(m_cjson);
	fputs(json_str, f);
	free(json_str);
	fclose(f);
}

Value::Value(cJSON* cjson)
{
	m_cjson = cjson;
}

Value::Value(int val)
{
	m_cjson = cJSON_CreateNumber(val);
}

Value::Value(float val)
{
	m_cjson = cJSON_CreateNumber(val);
}

Value::Value(bool val)
{
	m_cjson = cJSON_CreateBool(val);
}

Value::Value(const char* str)
{
	m_cjson = cJSON_CreateString(str);
}

Value::Value(Array&& arr)
{
	m_cjson = ((Array&&)arr).release();
}

Value::Value(Object&& obj)
{
	m_cjson = ((Object&&)obj).release();
}

Value::~Value()
{
	if (m_cjson)
		delete m_cjson;
}

cJSON* Value::release() &&
{
	auto* ptr = m_cjson;
	m_cjson = nullptr;
	return ptr;
}

Value_View Value::get_view() const
{
	return Value_View{m_cjson};
}

Array::Array()
{
	m_cjson = cJSON_CreateArray();
}

Array::Array(Array&& other)
{
	m_cjson = ((Array&&)other).release();
}

Array::~Array()
{
	if (m_cjson)
		delete m_cjson;
}

cJSON* Array::release() &&
{
	auto* ptr = m_cjson;
	m_cjson = nullptr;
	return ptr;
}

cJSON* Object::release() &&
{
	auto* ptr = m_cjson;
	m_cjson = nullptr;
	return ptr;
}

Array_View Array::get_view() const
{
	return Array_View{m_cjson};
}

void Object::add(const char* key, Value&& val)
{
	cJSON_AddItemToObject(m_cjson, key, ((Value&&)val).release());
}

void Array::add(JSON::Value&& value)
{
	cJSON_AddItemToArray(m_cjson, ((JSON::Value&&)value).release());
}

}

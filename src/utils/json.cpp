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
	m_cjson = cjson;
}

int Value_View::as_int(int fallback_value) const
{
	if (cJSON_IsNumber(m_cjson)) {
		return m_cjson->valueint;
	} else {
		SG_ERROR("JSON: Expected an integer.");
		return fallback_value;
	}
}

bool Value_View::as_bool(bool fallback_value) const
{
	if (cJSON_IsBool(m_cjson)) {
		return m_cjson->valueint;
	} else {
		SG_ERROR("JSON: Expected a boolean.");
		return fallback_value;
	}
}

float Value_View::as_float(float fallback_value) const
{
	if (cJSON_IsNumber(m_cjson)) {
		return m_cjson->valuedouble;
	} else {
		SG_ERROR("JSON: Expected a number.");
		return fallback_value;
	}
}

const char* Value_View::as_string(const char* fallback_value) const
{
	if (cJSON_IsString(m_cjson)) {
		return m_cjson->valuestring;
	} else {
		SG_ERROR("JSON: Expected a string.");
		return fallback_value;
	}
}

Array_View Value_View::as_array() const
{
	if (cJSON_IsArray(m_cjson)) {
		return Array_View{m_cjson};
	} else {
		SG_ERROR("JSON: Expected an array.");
		return Array_View{nullptr};
	}
}

Object_View Value_View::as_object() const
{
	if (cJSON_IsObject(m_cjson)) {
		return Object_View{m_cjson};
	} else {
		SG_ERROR("JSON: Expected an object.");
		return Object_View{nullptr};
	}
}

bool Value_View::is_null() const
{
	return cJSON_IsNull(m_cjson);
}

bool Value_View::is_array() const
{
	return cJSON_IsArray(m_cjson);
}

bool Value_View::is_string() const
{
	return cJSON_IsString(m_cjson);
}

Object_View::Object_View(const cJSON* cjson)
{
	if (cjson)
		assert(cJSON_IsObject(cjson));

	m_cjson = cjson;
}

bool Object_View::has(const char* key) const
{
	return cJSON_HasObjectItem(m_cjson, key);
}

Value_View Object_View::get(const char* key) const
{
	cJSON* item = cJSON_GetObjectItem(m_cjson, key);
	if (!item) {
		SG_ERROR("JSON: Missing object key \"%s\".", key);
	}
	return Value_View(item);
}

Array_View::Array_View(const cJSON* cjson)
{
	if (cjson)
		assert(cJSON_IsArray(cjson));

	m_cjson = cjson;
}

Object::~Object()
{
	if (m_cjson)
		cJSON_Delete(m_cjson);
}

Object::Object()
{
	m_cjson = cJSON_CreateObject();
}

Object::Object(cJSON* cjson)
{
	m_cjson = cjson;
}

Object::Object(Object&& other)
{
	m_cjson = ((Object&&)other).release();
}

Object_View Object::get_view() const
{
	return Object_View{m_cjson};
}

Object Object::from_file(const char* filename)
{
	String file_content = read_file_to_str(filename);
	cJSON* cjson = cJSON_Parse(file_content.data());

	if (cJSON_IsObject(cjson)) {
		return Object{cjson};
	} else {
		SG_ERROR("Error when parsing JSON file \"%s\"", filename);

		if (cjson)
			cJSON_Delete(cjson);

		return Object{};
	}
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

Value::Value(double val)
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

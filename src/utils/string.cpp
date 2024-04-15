#include "string.hpp"
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

String String::from_int(int value)
{
	char str[32];
	sprintf(str, "%d", value);
	return String{str};
}

String::String(const char* init)
{
	int len = strlen(init);
	reserve(len);
	strcpy(m_data, init);
	m_length = len;
}

String::String(String&& other)
{
	m_data = other.m_data;
	m_capacity = other.m_capacity;
	m_length = other.m_length;

	other.m_length = 0;
	other.m_capacity = 0;
	other.m_data = nullptr;
}

String& String::operator=(String&& other)
{
	if (m_data)
	{
		free(m_data);
	}

	m_data = other.m_data;
	m_capacity = other.m_capacity;
	m_length = other.m_length;

	other.m_length = 0;
	other.m_capacity = 0;
	other.m_data = nullptr;

	return *this;
}

String& String::operator=(const String& other)
{
	clear();
	append(other);

	return *this;
}

String::String(const String& other)
{
	append(other);
}

String::~String()
{
	if (m_data)
	{
		free(m_data);
	}
}

bool String::operator==(const char* other) const
{
	if (m_data == other)
		return true;

	if (m_data == nullptr || other == nullptr)
		return false;

	return strcmp(data(), other) == 0;
}

bool String::operator==(const String& other) const
{
	return *this == other.data();
}

void String::clear()
{
	m_length = 0;

	if (m_capacity > 0)
	{
		m_data[0] = 0;
	}
}

char& String::operator[](int index)
{
	assert(index < m_length);
	return m_data[index];
}

const char& String::operator[](int index) const
{
	assert(index < m_length);
	return m_data[index];
}

void String::append(char new_char)
{
	if (m_length + 1 >= m_capacity) // add 1 to accomodate for terminating null character
	{
		if (m_capacity <= 1) // empty string
			reserve(2);
		else
			reserve(m_capacity * 2);
	}

	m_data[m_length++] = new_char;
	m_data[m_length] = 0;
}

void String::append(const String& new_string)
{
	// NOTE - this can be optimized greatly
	for (int i = 0; i < new_string.length(); i++)
	{
		append(new_string[i]);
	}
}

void String::reserve(int length)
{
	m_data = (char*)realloc(m_data, length + 1);
	m_capacity = length;
}

void String::pop()
{
	if (empty())
		return;

	m_length -= 1;
	m_data[m_length] = 0;
}

bool String::has_prefix(const String& other) const
{
	if (other.length() > length())
		return false;

	for (int i = 0; i < other.length(); i++)
	{
		if ((*this)[i] != other[i])
			return false;
	}

	return true;
}

bool String::has_postfix(const String& other) const
{
	if (other.length() > length())
		return false;

	return strcmp(other.data(), data() + (length() - other.length())) == 0;
}

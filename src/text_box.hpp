#pragma once

#include "utils/array.hpp"
#include "utils/string.hpp"

class Text_Box
{
public:
	bool contains_message() const;
	const String& get_displayed_message() const;
	void push_message(String&&);
	void advance();
private:
	// NOTE - a queue-like data structure would probably be better.
	Array<String> m_messages;
	int m_current_message = 0;
};

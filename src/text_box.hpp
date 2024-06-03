#pragma once

#include "utils/array.hpp"
#include "utils/string.hpp"

class Text_Box
{
public:
	bool contains_message() const;
	String get_displayed_message() const;
	int get_displayed_character_count() const;
	void push_message(String&&);
	void update(float time_delta);
	void advance();
private:
	// NOTE - a queue-like data structure would probably be better.
	Array<String> m_messages;
	int m_current_message = 0;
	float m_time_shown = 0;
};

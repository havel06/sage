#include "input_state.hpp"
#include <ctype.h>
#include "utils/move.hpp"
#include "utils/minmax.hpp"

// <math.h> fwd
extern "C"
{
double fmod(double, double);
}

namespace Editor_UI::Widgets
{

void Input_State::set_content(const String& new_content)
{
	m_content = new_content;
	m_cursor_position = m_content.length();
	choose_new_hint();
}

void Input_State::insert_character(char character)
{
	if (!active)
		return;

	if (m_cursor_position == m_content.length()) {
		// Cursor on end
		m_content.append(character);
		choose_new_hint();
	} else {
		// Insert text on cursor position
		String before_cursor = m_content.substring(0, m_cursor_position);
		String after_cursor = m_content.substring(m_cursor_position, m_content.length() - m_cursor_position);

		m_content = before_cursor;
		m_content.append(character);
		m_content.append(after_cursor);
		choose_new_hint();
	}

	m_cursor_position++;
	fix_cursor_position();
}

void Input_State::delete_character()
{
	if (m_cursor_position == m_content.length()) {
		// Remove last character
		m_content.pop();
	} else if (m_cursor_position != 0) {
		// Remove character at position
		String content_before = m_content.substring(0, m_cursor_position - 1);
		String content_after = m_content.substring(m_cursor_position, m_content.length() - m_cursor_position);
		m_content = content_before;
		m_content.append(content_after);
		m_cursor_position--;
	}

	choose_new_hint();
	fix_cursor_position();
}

void Input_State::delete_last_word()
{
	if (m_content.empty())
		return;

	auto is_separator = [](char c) {
		return isspace(c) || c == '/';
	};

	// Iterate from end of content until we find a separator character
	// after deleting at least one non-separator charcter
	bool found_non_sep = false;
	int i = m_content.length() - 1;
	for (; i >= 0; i--) {
		if (!is_separator(m_content[i])) {
			found_non_sep = true;
		} else if (found_non_sep) {
			i++; // Leave the separator
			break;
		}
	}

	if (i <= 0) {
		m_content.clear();
	} else {
		m_content = m_content.substring(0, i);
	}
	fix_cursor_position();
	choose_new_hint();
}

void Input_State::move_cursor_left()
{
	m_cursor_position--;
	fix_cursor_position();
}

void Input_State::move_cursor_right()
{
	m_cursor_position++;
	fix_cursor_position();
}

void Input_State::set_hints(const Array<String>& hints)
{
	m_hints = hints;
	choose_new_hint();
}

void Input_State::fix_cursor_position()
{
	if (m_cursor_position < 0)
		m_cursor_position = 0;
	else if (m_cursor_position > m_content.length())
		m_cursor_position = m_content.length();
}

void Input_State::choose_new_hint()
{
	for (const String& hint : m_hints) {
		if (hint.has_prefix(m_content)) {
			m_current_displayed_hint = hint;
			return;
		}
	}
}

void Input_State::use_hint()
{
	// Find matching hints
	Array<const String*> matching_hints;
	int minimum_length = 999999;

	for (const String& hint : m_hints) {
		if (hint.has_prefix(m_content)) {
			matching_hints.push_back(&hint);
			minimum_length = min(hint.length(), minimum_length);
		}
	}

	if (matching_hints.empty())
		return;

	// Find longest common prefix
	int prefix_length = 0;
	while (prefix_length < minimum_length) {
		// Check if all of the matching hints have the same character
		// at given position
		char matched_character = (*(matching_hints[0]))[prefix_length];
		bool all_chars_matching = true;

		for (int i = 0; i < matching_hints.size(); i++) {
			char c = (*(matching_hints[i]))[prefix_length];
			if (c != matched_character) {
				all_chars_matching = false;
				break;
			}
		}

		if (!all_chars_matching)
			break;

		prefix_length++;
	}

	// Use longest common prefix
	m_content = matching_hints[0]->substring(0, prefix_length);
	m_cursor_position = m_content.length();
}

}

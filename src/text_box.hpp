#pragma once

#include "graphics/game_ui/formatted_text.hpp"
#include "utils/array.hpp"
#include "utils/string.hpp"

class Text_Box
{
public:
	bool contains_message() const;
	const Game_UI::Formatted_Text& get_displayed_message() const;
	int get_displayed_character_count() const;
	void push_message(const Game_UI::Formatted_Text&);
	void update(float time_delta);
	void advance();
private:
	// NOTE - a queue-like data structure would probably be better.
	Array<Game_UI::Formatted_Text> m_messages;
	int m_current_message = 0;
	float m_time_shown = 0;
};

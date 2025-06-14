#include "text.hpp"
#include "../formatted_text.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"
#include "../widget_visitor.hpp"

namespace Game_UI
{

Text::Text(Resource_Handle<Font> font, Layout&& layout) :
	Widget((Layout&&)layout),
	m_font{font}
{
}

void Text::draw_impl(Recti parent_area, float opacity, float)
{
	const Array<Formatted_Text> lines = wrap_text(text, parent_area.size.x);

	// Draw the lines
	float y = parent_area.position.y;
	for (const Formatted_Text& line : lines) {
		draw_line(line, parent_area.position.x, y, parent_area.size.x, opacity);
		y += size * 1.25;
	}
}

void Text::draw_line(const Formatted_Text& line, int x, int y, int max_width, float opacity)
{
	const int width = MeasureTextEx(m_font.get(), line.to_string().data(), size, 0).x;
	const int space_left = max_width - width;
	const int offset = align == Text_Align::center ? (space_left / 2) : 0;
	x += offset;

	// Draw individual fragments
	for (const Formatted_Text_Fragment& fragment : line.fragments) {
		const int fragment_width = MeasureTextEx(m_font.get(), fragment.text.data(), size, 0).x;
		Colour fragment_colour = fragment.colour.has_value() ? fragment.colour.value() : colour;
		fragment_colour.a *= opacity;
		DrawTextEx(m_font.get(), fragment.text.data(), {(float)x, (float)y}, size, 0, fragment_colour.to_ray_color());
		x += fragment_width;
	}
}

Array<Formatted_Text_Fragment> Text::split_text_to_words(const Formatted_Text& text)
{
	Array<Formatted_Text_Fragment> words;

	Formatted_Text_Fragment word;

	for (const Formatted_Text_Fragment& fragment : text.fragments) {
		word.colour = fragment.colour;

		for (int i = 0; i < fragment.text.length(); i++) {
			char c = fragment.text[i];
			if (c == ' ') {
				if (!word.text.empty()) {
					words.push_back(word);
					word.text.clear();
				}
			} else if (c == '\n') {
				words.push_back(word);
				words.push_back(Formatted_Text_Fragment{.text = "\n"});
				word.text.clear();
			} else {
				word.text.append(c);
			}
		}

		// Add last word
		if (!word.text.empty()) {
			words.push_back(word);
			word.text.clear();
		}
	}

	return words;
}

Array<Formatted_Text> Text::wrap_text(const Formatted_Text& text, int width)
{
	auto words = split_text_to_words(text);
	
	// If whole text fits on one line, just return it right away
	//String first_line_test;
	//for (int i = 0; i < words.size(); i++) {
	//	first_line_test.append(words[i].text);
	//	if (words[i].text != "\n")
	//		first_line_test.append(" ");
	//} if (MeasureText(first_line_test.data(), size) <= width) {
	//	Array<Formatted_Text_Fragment> result;
	//	result.push_back(first_line_test);
	//	return result;
	//}

	// Wrap text
	Array<Formatted_Text> result;
	Formatted_Text line;

	for (const Formatted_Text_Fragment& word : words) {
		if (word.text == "\n") {
			result.push_back(line);
			line.fragments.clear();
			continue;
		}

		auto space_left = width - MeasureTextEx(m_font.get(), line.to_string().data(), size, 0).x;

		const auto word_width = MeasureTextEx(m_font.get(), word.text.data(), size, 0).x;
		if (word_width <= space_left) {
			//add word to current line
			line.fragments.push_back(word);
			line.fragments.push_back(Formatted_Text_Fragment{.text = " "});
		} else {
			//new line
			result.push_back(line);
			line.fragments.clear();
			line.fragments.push_back(word);
			line.fragments.push_back(Formatted_Text_Fragment{.text = " "});
		}
	}
	//add last line
	if (!line.fragments.empty()) {
		result.push_back(line);
	}
	
	return result;
}

Widget_Ptr Text::clone_impl(Layout&& layout) const
{
	Own_Ptr<Text> cloned = make_own_ptr<Text>(m_font, (Layout&&)layout);
	cloned->text = text;
	cloned->size = size;
	cloned->align = align;
	cloned->colour = colour;
	return cloned;
}

void Text::accept_visitor(Widget_Visitor& visitor)
{
	visitor.visit_text(*this);
}

}

#include "text.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"
#include "widget_visitor.hpp"

namespace UI
{

Text::Text(Resource_Handle<Font> font, Layout&& layout) :
	Widget((Layout&&)layout),
	m_font{font}
{
}

void Text::draw_impl(Recti parent_area, float opacity, float)
{
	const Color color {255, 255, 255, (unsigned char)(255 * opacity)};
	const Array<String> wrapped_text = wrap_text(text, parent_area.size.x);

	// Draw the lines
	float y = parent_area.position.y;
	for (const String& line : wrapped_text) {
		draw_line(line, parent_area.position.x, y, parent_area.size.x, color);
		y += size * 1.25;
	}
}

void Text::draw_line(const String& line, int x, int y, int max_width, Color color)
{
	const int width = MeasureTextEx(m_font.get(), line.data(), size, 0).x;
	const int space_left = max_width - width;
	const int offset = align == Text_Align::center ? (space_left / 2) : 0;

	DrawTextEx(m_font.get(), line.data(), {(float)(x + offset), (float)y}, size, 0, color);
}

Array<String> Text::split_text_to_words(const String& text)
{
	Array<String> words;
	String word;
	for (int i = 0; i < text.length(); i++) {
		char c = text[i];
		if (c == ' ' && !word.empty()) {
			words.push_back(word);
			word.clear();
		} else if (c == '\n') {
			words.push_back(word);
			words.push_back("\n");
			word.clear();
		} else {
			word.append(c);
		}
	}
	// Add last word
	if (!word.empty()) {
		words.push_back(word);
	}

	return words;
}

Array<String> Text::wrap_text(const String& text, int width)
{
	auto words = split_text_to_words(text);
	
	// If whole text fits on one line, just return it right away
	String first_line_test;
	for (int i = 0; i < words.size(); i++) {
		first_line_test.append(words[i]);
		if (words[i] != "\n")
			first_line_test.append(" ");
	} if (MeasureText(first_line_test.data(), size) <= width) {
		Array<String> result;
		result.push_back(first_line_test);
		return result;
	}

	// Wrap text
	Array<String> result;
	String line;
	for (int i = 0; i < words.size(); i++) {
		if (words[i] == "\n") {
			line.append("\n");
			continue;
		}

		auto space_left = width - MeasureTextEx(m_font.get(), line.data(), size, 0).x;

		const auto word_width = MeasureTextEx(m_font.get(), (words[i]).data(), size, 0).x;
		if (word_width <= space_left) {
			//add word to current line
			line.append(words[i]);
			line.append(" ");
		} else {
			//new line
			result.push_back(line);
			line = words[i];
			line.append(" ");
		}
	}
	//add last line
	if (!line.empty()) {
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
	return cloned;
}

void Text::accept_visitor(Widget_Visitor& visitor)
{
	visitor.visit_text(*this);
}

}

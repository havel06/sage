#include "text.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"

namespace UI
{

Text::Text(Resource_Handle<Font> font, Layout&& layout) :
	Widget((Layout&&)layout),
	m_font{font}
{
}

void Text::draw_impl(Recti parent_area, float opacity, float)
{
	const String wrapped_text = wrap_text(text, parent_area.size.x);
	const Color color {255, 255, 255, (unsigned char)(255 * opacity)};
	DrawTextEx(m_font.get(), wrapped_text.data(), {(float)parent_area.position.x, (float)parent_area.position.y}, size, 0, color);
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

String Text::wrap_text(const String& text, int width)
{
	auto words = split_text_to_words(text);
	
	// If whole text fits on one line, just return it right away
	String first_line_test;
	for (int i = 0; i < words.size(); i++) {
		first_line_test.append(words[i]);
		if (words[i] != "\n")
			first_line_test.append(" ");
	} if (MeasureText(first_line_test.data(), size) <= width) {
		return {first_line_test};
	}

	// Wrap text
	String result;
	String line;
	for (int i = 0; i < words.size(); i++) {
		if (words[i] == "\n") {
			line.append("\n");
			continue;
		}

		auto space_left = width - MeasureTextEx(m_font.get(), line.data(), size, 0).x;

		const auto word_width = MeasureText((words[i]).data(), size);
		if (word_width <= space_left) {
			//add word to current line
			line.append(words[i]);
			line.append(" ");
		} else {
			//new line
			result.append(line);
			result.append("\n");
			line = words[i];
			line.append(" ");
		}
	}
	//add last line
	if (!line.empty()) {
		result.append(line);
	}
	
	return result;
}

Widget_Ptr Text::clone_impl(Layout&& layout) const
{
	Own_Ptr<Text> cloned = make_own_ptr<Text>(m_font, (Layout&&)layout);
	cloned->text = text;
	cloned->size = size;
	return cloned;
}

}

#include "text.hpp"
#include "raylib/raylib.h"

namespace UI
{

Text::Text(Layout&& layout) :
	Widget((Layout&&)layout)
{
}

void Text::draw_impl(Recti parent_area, float)
{
	String wrapped_text = wrap_text(text, parent_area.size.x);
	DrawText(wrapped_text.data(), parent_area.position.x, parent_area.position.y, size, WHITE);
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

		auto space_left = width - MeasureText(line.data(), size);

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

}

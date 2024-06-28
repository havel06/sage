#pragma once

#include "widget.hpp"
#include "utils/string.hpp"
#include <raylib/raylib.h>

namespace UI
{

class Text : public Widget
{
public:
	Text(Layout&&);
	Font font = GetFontDefault();
	String text = "";
	int size = 10;
private:
	void draw_impl(Recti parent_area, float time_delta) override;
	Widget_Ptr clone_impl(Layout&&) const override;
	Array<String> split_text_to_words(const String& text);
	String wrap_text(const String& text, int width);
	bool is_focusable() const override { return false; }
};

}

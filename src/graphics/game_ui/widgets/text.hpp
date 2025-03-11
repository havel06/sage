#pragma once

#include "../widget.hpp"
#include "utils/string.hpp"
#include "io/resource/resource_handle.hpp"
#include "../formatted_text.hpp"
#include <raylib/raylib.h>

namespace Game_UI
{

enum class Text_Align
{
	left,
	center
};

class Text : public Widget
{
public:
	Formatted_Text text;
	int size = 10;
	Text_Align align = Text_Align::left;

	Text(Resource_Handle<Font>, Layout&&);
	void accept_visitor(Widget_Visitor&) override;
private:
	void draw_impl(Recti parent_area, float opacity, float time_delta) override;
	Widget_Ptr clone_impl(Layout&&) const override;
	void draw_line(const Formatted_Text& line, int x, int y, int max_width, float opacity, Colour fallback_color);
	Array<Formatted_Text_Fragment> split_text_to_words(const Formatted_Text& text);
	Array<Formatted_Text> wrap_text(const Formatted_Text& text, int width); // Array of lines
	bool is_focusable() const override { return false; }
	void process_click_impl() override {}

	Resource_Handle<Font> m_font;
};

}

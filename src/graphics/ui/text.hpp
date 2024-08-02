#pragma once

#include "widget.hpp"
#include "utils/string.hpp"
#include "io/resource/resource_handle.hpp"
#include <raylib/raylib.h>

namespace UI
{

class Text : public Widget
{
public:
	String text = "";
	int size = 10;
	Text(Resource_Handle<Font>, Layout&&);
	void accept_visitor(Widget_Visitor&) override;
private:
	void draw_impl(Recti parent_area, float opacity, float time_delta) override;
	Widget_Ptr clone_impl(Layout&&) const override;
	Array<String> split_text_to_words(const String& text);
	String wrap_text(const String& text, int width);
	bool is_focusable() const override { return false; }
	void process_click_impl() override {}

	Resource_Handle<Font> m_font;
};

}

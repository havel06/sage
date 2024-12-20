#pragma once

#include "widget.hpp"
#include "utils/string.hpp"
#include "graphics/sprite.hpp"

namespace Game_UI
{

class Image : public Widget
{
public:
	Sprite sprite;
	Image(Layout&&);
	void accept_visitor(Widget_Visitor&) override;
private:

	void draw_impl(Recti parent_area, float opacity, float time_delta) override;
	Widget_Ptr clone_impl(Layout&&) const override;
	bool is_focusable() const override { return false; }
	void process_click_impl() override {}
};

}
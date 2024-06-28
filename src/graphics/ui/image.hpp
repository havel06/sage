#pragma once

#include "widget.hpp"
#include "utils/string.hpp"
#include "graphics/sprite.hpp"

namespace UI
{

class Image : public Widget
{
public:
	Sprite sprite;
	Image(Layout&&);
private:

	void draw_impl(Recti parent_area, float time_delta) override;
	Widget_Ptr clone_impl(Layout&&) const override;
	bool is_focusable() const override { return false; }
	void process_click_impl() override {}
};

}

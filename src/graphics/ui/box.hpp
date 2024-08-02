#pragma once

#include "widget.hpp"
#include "utils/colour.hpp"

namespace UI
{

class Box : public Widget
{
public:
	Box(Layout&&);
	Colour colour = {0, 0, 0, 0};
	void accept_visitor(Widget_Visitor&) override;
private:
	void draw_impl(Recti parent_area, float opacity, float time_delta) override;
	Widget_Ptr clone_impl(Layout&&) const override;
	bool is_focusable() const override { return false; }
	void process_click_impl() override {}
};

}

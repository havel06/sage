#pragma once

#include "widget.hpp"
#include "utils/function_wrapper.hpp"

namespace UI
{

class Button : public Widget
{
public:
	Function_Wrapper<void()> on_click;

	Button(Widget_Ptr&& normal, Widget_Ptr&& focused, Layout&&);
private:
	Widget_Ptr m_content_normal;
	Widget_Ptr m_content_focused;

	void draw_impl(Recti parent_area, float time_delta) override;
	Widget_Ptr clone_impl(Layout&&) const override;
	bool is_focusable() const override { return true; }
	void process_click_impl() override;
};

}

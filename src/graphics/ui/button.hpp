#pragma once

#include "widget.hpp"

namespace UI
{

class Button : public Widget
{
public:
	Button(Widget_Ptr&& normal, Widget_Ptr&& focused, Layout&&);
private:
	Widget_Ptr m_content_normal;
	Widget_Ptr m_content_focused;

	void draw_impl(Recti parent_area, float time_delta) override;
	Widget_Ptr clone_impl(Layout&&) const override;
};

}

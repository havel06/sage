#pragma once

#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "utils/rect.hpp"

namespace UI
{

//fwd
class Widget;

using Widget_Ptr = Own_Ptr<Widget>;


class Widget_Collection
{
public:
	void add_widget(Widget_Ptr&&);
	// Should only be called by parent widget
	void draw(Recti parent_area, float time_delta);
private:
	Array<Widget_Ptr> m_widgets;
};


class Widget
{
public:
	void draw(Recti parent_area, float time_delta);
	void add_child(Widget_Ptr&&);
private:
	Widget_Collection m_children;
	virtual void draw_impl(Recti parent_area, float time_delta) = 0;
};

}

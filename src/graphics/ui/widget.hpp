#pragma once

#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "utils/rect.hpp"

namespace UI
{

//fwd
class Widget;

using Widget_Ptr = Own_Ptr<Widget>;


struct Layout_Element
{
	int row;
	int column;
	Widget_Ptr widget;
};

class Layout
{
public:
	// Rows and columns are on a scale from 0 to 1
	Layout(const Array<float> rows, const Array<float>& columns);
	void add(Layout_Element&&);
	// Should only be called by parent widget
	void draw(Recti parent_area, float time_delta);
private:
	Array<float> m_columns;
	Array<float> m_rows;
	Array<Layout_Element> m_elements;
};


class Widget
{
public:
	Widget(Layout&&);
	virtual ~Widget() = default;
	void draw(Recti parent_area, float time_delta);
	void add_child(Widget_Ptr&&, int row, int column);
private:
	Layout m_layout;
	virtual void draw_impl(Recti parent_area, float time_delta) = 0;
};

}

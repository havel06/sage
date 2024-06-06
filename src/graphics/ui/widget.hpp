#pragma once

#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "utils/rect.hpp"
#include "utils/string.hpp"

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
	Layout(const Array<float>& rows, const Array<float>& columns);
	Layout();
	void add(Layout_Element&&);
	// Should only be called by parent widget
	void draw(Recti parent_area, float time_delta);
	Widget* get_widget_by_name(const String&);
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
	void set_name(String&&);
	void draw(Recti parent_area, float time_delta);
	void draw_as_root(float time_delta);
	void add_child(Widget_Ptr&&, int row, int column);
	Widget* get_widget_by_name(const String&);
private:
	String m_name = "";
	Layout m_layout;
	virtual void draw_impl(Recti parent_area, float time_delta) = 0;
};

}

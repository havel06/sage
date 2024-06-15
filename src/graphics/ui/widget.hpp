#pragma once

#include "size.hpp"
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

// FIXME - separate file
class Layout
{
public:
	// Rows and columns are on a scale from 0 to 1
	Layout(const Array<Size>& rows, const Array<Size>& columns);
	Layout();
	void add(Widget_Ptr&&, int row, int column);
	void add(Widget_Ptr&&);
	// Should only be called by parent widget
	void draw(Recti parent_area, float time_delta);
	Widget* get_widget_by_name(const String&);
	Layout clone() const;
	void clear();
private:
	// FIXME - specify expand direction
	void expand();

	Array<Size> m_columns;
	Array<Size> m_rows;
	Array<Layout_Element> m_elements;
};


class Widget
{
public:
	Widget(Layout&&);
	virtual ~Widget() = default;
	Widget_Ptr clone() const;
	void set_name(String&&);
	void draw(Recti parent_area, float time_delta);
	void draw_as_root(float time_delta);
	void add_child(Widget_Ptr&&, int row, int column);
	void add_child(Widget_Ptr&&);
	void clear_children();
	Widget* get_widget_by_name(const String&);
private:
	String m_name = "";
	Layout m_layout;
	virtual void draw_impl(Recti parent_area, float time_delta) = 0;
	virtual Widget_Ptr clone_impl(Layout&&) const = 0;
};

}

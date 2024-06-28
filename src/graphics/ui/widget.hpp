#pragma once

#include "size.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "utils/rect.hpp"
#include "utils/string.hpp"
#include "utils/direction.hpp"

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

enum class Focus_Move_Result
{
	no_action,
	moved,
	out_of_bounds
};

// FIXME - separate file
class Layout
{
public:
	// Rows and columns are on a scale from 0 to 1
	Layout(const Array<Size>& rows, const Array<Size>& columns);
	Layout();
	Layout clone() const;

	void add(Widget_Ptr&&, int row, int column);
	void add(Widget_Ptr&&);
	void clear();
	Widget* get_widget_by_name(const String&);
	Widget* get_widget_by_position(int row, int column);

	// Should only be called by parent widget
	void draw(Recti parent_area, float time_delta);
	// Should only be called by parent widget
	void process_click();

	// Should only be called once.
	// Returns true when focus was successful.
	bool focus_first();
	Focus_Move_Result move_focus(Direction);
	Widget* get_focused_widget();
private:
	// FIXME - rename
	Array<int> calculate_rows_or_columns(const Array<Size>&, Vec2i parent_size, int direction_size);
	// FIXME - specify expand direction
	void expand();
	bool focus_next(Direction, int row, int column);

	Array<Size> m_columns;
	Array<Size> m_rows;
	Array<Layout_Element> m_elements;
};


// FIXME - consider refactoring
class Widget
{
public:
	Widget(Layout&&);
	virtual ~Widget() = default;

	Widget_Ptr clone() const;
	void set_name(String&&);

	void draw(Recti parent_area, float time_delta);
	void draw_as_root(float time_delta);
	void process_click();

	// Should only be called once.
	// Returns true when focus was successful.
	bool focus_first();
	void lose_focus();
	Focus_Move_Result move_focus(Direction);
	Widget* get_focused_widget();

	void add_child(Widget_Ptr&&, int row, int column);
	void add_child(Widget_Ptr&&);
	void clear_children();
	Widget* get_widget_by_name(const String&);

protected:
	bool is_focused() const { return m_focused; }

private:
	bool m_focused = false;
	String m_name = "";
	Layout m_layout;

	virtual void draw_impl(Recti parent_area, float time_delta) = 0;
	virtual void process_click_impl() = 0;
	virtual Widget_Ptr clone_impl(Layout&&) const = 0;
	virtual bool is_focusable() const = 0;
};

}

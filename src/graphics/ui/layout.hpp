#pragma once

#include "size.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "utils/string.hpp"
#include "utils/direction.hpp"
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

enum class Focus_Move_Result
{
	no_action,
	moved,
	out_of_bounds
};

// FIXME - consider refactoring
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

}

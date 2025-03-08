#include "layout.hpp"
#include "widget.hpp"
#include "utils/log.hpp"

namespace Game_UI
{

Layout::Layout(const Array<Size>& rows, const Array<Size>& columns)
{
	assert(rows.size() > 0);
	assert(columns.size() > 0);

	m_rows = rows;
	m_columns = columns;
}

Layout::Layout()
{
	m_columns.push_back(Size{ .parent_width = 1 });
	m_rows.push_back(Size{ .parent_height = 1 });
}

void Layout::add(Widget_Ptr&& widget, int row, int column)
{
	assert(row < m_rows.size());
	assert(row >= 0);
	assert(column < m_columns.size());
	assert(column >= 0);

	m_elements.push_back(Layout_Element{
		.row = row,
		.column = column,
		.widget = (Widget_Ptr&&)widget,
	});

}

void Layout::add(Widget_Ptr&& widget)
{
	// Find free spot
	// NOTE - possible optimisation

	auto is_spot_free = [&](int row, int column) -> bool {
		for (int i = 0; i < m_elements.size(); i++) {
			if (m_elements[i].row == row && m_elements[i].column == column) {
				return false;
			}
		}
		return true;
	};

	// Add to free spot if possible
	for (int row = 0; row < m_rows.size(); row++) {
		for (int column = 0; column < m_columns.size(); column++) {
			if (is_spot_free(row, column)) {
				add((Widget_Ptr&&)widget, row, column);
				return;
			}
		}
	}

	// Expand the grid
	expand();
	add((Widget_Ptr&&)widget); // TODO - is there a better option than recursion?
}

void Layout::expand()
{
	m_rows.push_back(m_rows.back());
}

Array<int> Layout::calculate_rows_or_columns(const Array<Size>& rows_or_columns, Vec2i parent_size, int direction_size)
{
	int space_remaining = direction_size;
	int num_automatic = 0; // How many automatic rows/columns

	// First pass - calculate remaining space and number of automatic rows/columns
	for (int i = 0; i < rows_or_columns.size(); i++) {
		if (rows_or_columns[i].automatic) {
			num_automatic++;
		} else {
			space_remaining -= rows_or_columns[i].to_pixels(parent_size);
		}
	}

	const int size_per_auto = num_automatic == 0 ? 0 : space_remaining / num_automatic;

	Array<int> result;

	// Second pass - calculate specific sizes
	for (int i = 0; i < rows_or_columns.size(); i++) {
		if (rows_or_columns[i].automatic) {
			result.push_back(size_per_auto);
		} else {
			result.push_back(rows_or_columns[i].to_pixels(parent_size));
		}
	}

	return result;
}

void Layout::draw(Recti parent_area, float parent_opacity, float time_delta)
{
	// FIXME - refactor?

	if (m_elements.empty())
		return;

	const Array<int> rows = calculate_rows_or_columns(m_rows, parent_area.size, parent_area.size.y);
	const Array<int> columns = calculate_rows_or_columns(m_columns, parent_area.size, parent_area.size.x);

	for (int i = 0; i < m_elements.size(); i++) {
		const Layout_Element& element = m_elements[i];
		Recti widget_area = {parent_area.position, {0, 0}};

		// Calculate offset
		for (int i = 0; i < element.column; i++) {
			widget_area.position.x += columns[i];
		}
		for (int i = 0; i < element.row; i++) {
			widget_area.position.y += rows[i];
		}

		// Size
		widget_area.size.x = columns[element.column];
		widget_area.size.y = rows[element.row];

		m_elements[i].widget->draw(widget_area, parent_opacity, time_delta);
	}
}

Layout Layout::clone() const
{
	Layout cloned{m_rows, m_columns};

	for (int i = 0; i < m_elements.size(); i++) {
		const Layout_Element& element = m_elements[i];
		cloned.add(element.widget->clone(), element.row, element.column);
	}

	return cloned;
}

Widget* Layout::get_widget_by_name(const String& name)
{
	for (int i = 0; i < m_elements.size(); i++) {
		Widget* maybe_found = m_elements[i].widget->get_widget_by_name(name);
		if (maybe_found)
			return maybe_found;
	}

	return nullptr;
}

void Layout::clear()
{
	m_elements.clear();
}

bool Layout::focus_first()
{
	for (int i = 0; i < m_elements.size(); i++)	{
		Widget& widget = *(m_elements[i].widget);
		if (widget.focus_first()) {
			return true;
		}
	}

	return false;
}

void Layout::lose_focus()
{
	for (auto& element : m_elements) {
		element.widget->lose_focus();
	}
}

Focus_Move_Result Layout::move_focus(Direction direction)
{
	for (auto& element : m_elements) {
		switch (element.widget->move_focus(direction)) {
			case Focus_Move_Result::moved:
				return Focus_Move_Result::moved;

			case Focus_Move_Result::no_action:
				continue;

			case Focus_Move_Result::out_of_bounds:
				if (focus_next(direction, element.row, element.column)) {
					element.widget->lose_focus();
					return Focus_Move_Result::moved;
				} else {
					return Focus_Move_Result::out_of_bounds;
				}
		}
	}

	return Focus_Move_Result::no_action;
}

bool Layout::focus_next(Direction direction, int current_row, int current_column)
{
	switch (direction) {
		case Direction::up:
			for (int row = current_row - 1; row >= 0; row--) {
				Widget* w = get_widget_by_position(row, current_column);
				if (w && w->focus_first()) {
					return true;
				}
			}
			return false;
		case Direction::down:
			for (int row = current_row + 1; row < m_rows.size(); row++) {
				Widget* w = get_widget_by_position(row, current_column);
				if (w && w->focus_first()) {
					return true;
				}
			}
			return false;
		case Direction::left:
			for (int column = current_column - 1; column >= 0; column--) {
				Widget* w = get_widget_by_position(current_row, column);
				if (w && w->focus_first()) {
					return true;
				}
			}
			return false;
		case Direction::right:
			for (int column = current_column + 1; column < m_columns.size(); column++) {
				Widget* w = get_widget_by_position(current_row, column);
				if (w && w->focus_first()) {
					return true;
				}
			}
			return false;
	}
}

Widget* Layout::get_focused_widget()
{
	for (int i = 0; i < m_elements.size(); i++) {
		Widget* maybe_found = m_elements[i].widget->get_focused_widget();

		if (maybe_found)
			return maybe_found;
	}

	return nullptr;
}

Widget* Layout::get_widget_by_position(int row, int column)
{
	for (int i = 0; i < m_elements.size(); i++) {
		if (m_elements[i].row == row && m_elements[i].column == column)
			return m_elements[i].widget.get();
	}

	return nullptr;
}

void Layout::process_click()
{
	for (int i = 0; i < m_elements.size(); i++) {
		m_elements[i].widget->process_click();
	}
}


}

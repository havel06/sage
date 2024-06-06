#include "widget.hpp"
#include "raylib/raylib.h"

namespace UI
{

Layout::Layout(const Array<float>& rows, const Array<float>& columns)
{
	m_rows = rows;
	m_columns = columns;
}

Layout::Layout()
{
	m_columns.push_back(1);
	m_rows.push_back(1);
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

	for (int row = 0; row < m_rows.size(); row++) {
		for (int column = 0; column < m_columns.size(); column++) {
			if (is_spot_free(row, column)) {
				add((Widget_Ptr&&)widget, row, column);
				return;
			}
		}
	}
}

void Layout::draw(Recti parent_area, float time_delta)
{
	// FIXME - refactor
	for (int i = 0; i < m_elements.size(); i++) {
		const Layout_Element& element = m_elements[i];
		Recti widget_area = {parent_area.position, {0, 0}};

		// Calculate offset
		for (int i = 0; i < element.column; i++) {
			widget_area.position.x += m_columns[i] * parent_area.size.x;
		}
		for (int i = 0; i < element.row; i++) {
			widget_area.position.y += m_rows[i] * parent_area.size.y;
		}

		// Size
		widget_area.size.x = m_columns[element.column] * parent_area.size.x;
		widget_area.size.y = m_rows[element.row] * parent_area.size.y;

		m_elements[i].widget->draw(widget_area, time_delta);
	}
}

Widget::Widget(Layout&& layout) :
	m_layout{(Layout&&)layout}
{
}

void Widget::add_child(Widget_Ptr&& widget, int row, int column)
{
	m_layout.add((Widget_Ptr&&)widget, row, column);
}

void Widget::add_child(Widget_Ptr&& widget)
{
	m_layout.add((Widget_Ptr&&)widget);
}

void Widget::draw(Recti parent_area, float time_delta)
{
	draw_impl(parent_area, time_delta);
	m_layout.draw(parent_area, time_delta);
}

void Widget::draw_as_root(float time_delta)
{
	Recti area = {
		{0, 0},
		{GetScreenWidth(), GetScreenHeight()}
	};

	draw(area, time_delta);
}

void Widget::set_name(String&& name)
{
	m_name = (String&&)name;
}

Widget* Widget::get_widget_by_name(const String& name)
{
	if (m_name == name) {
		return this;
	} else {
		return m_layout.get_widget_by_name(name);
	}
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

}

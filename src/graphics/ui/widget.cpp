#include "widget.hpp"
#include "raylib/raylib.h"
#include "utils/direction.hpp"
#include "utils/log.hpp"

namespace UI
{


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

Widget_Ptr Widget::clone() const
{
	Widget_Ptr cloned = clone_impl(m_layout.clone());
	cloned->set_name(String{m_name});
	return cloned;
}

void Widget::clear_children()
{
	m_layout.clear();
}

void Widget::lose_focus()
{
	m_focused = false;
}

bool Widget::focus_first()
{
	if (is_focusable()) {
		m_focused = true;
		return true;
	} else {
		return m_layout.focus_first();
	}
}

Focus_Move_Result Widget::move_focus(Direction direction)
{
	if (m_focused) {
		return Focus_Move_Result::out_of_bounds;
	} else {
		return m_layout.move_focus(direction);
	}
}

Widget* Widget::get_focused_widget()
{
	if (m_focused) {
		return this;
	} else {
		return m_layout.get_focused_widget();
	}
}

void Widget::process_click()
{
	process_click_impl();
	m_layout.process_click();
}

}

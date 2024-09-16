#include "widget.hpp"
#include "raylib/raylib.h"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include "utils/minmax.hpp"

namespace UI
{


Widget::Widget(Layout&& layout) :
	m_layout{(Layout&&)layout}
{
}

void Widget::show(bool value)
{
	m_should_show = value;
}

bool Widget::is_showing() const
{
	if (m_should_show) {
		return true;
	} else {
		return m_opacity > 0;
	}
}

void Widget::add_child(Widget_Ptr&& widget, int row, int column)
{
	m_layout.add((Widget_Ptr&&)widget, row, column);
}

void Widget::add_child(Widget_Ptr&& widget)
{
	m_layout.add((Widget_Ptr&&)widget);
}

void Widget::draw(Recti parent_area, float parent_opacity, float time_delta)
{
	if (fade_in_out_time == 0) {
		m_opacity = m_should_show ? 1.0f : 0.0f;
	} else {
		// Progress fade-in/out
		if (m_should_show) {
			m_opacity += (1.0f / fade_in_out_time) * time_delta;
			m_opacity = min(m_opacity, 1.0f); // Limit to 1
		} else {
			m_opacity -= (1.0f / fade_in_out_time) * time_delta;
			m_opacity = max(m_opacity, 0.0f); // Limit to 0
		}
	}

	draw_impl(parent_area, m_opacity * parent_opacity, time_delta);
	m_layout.draw(parent_area, m_opacity * parent_opacity, time_delta);
}

void Widget::draw_as_root(float time_delta)
{
	Recti area = {
		{0, 0},
		{GetScreenWidth(), GetScreenHeight()}
	};

	draw(area, 1, time_delta);
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
	cloned->fade_in_out_time = this->fade_in_out_time;
	return cloned;
}

void Widget::clear_children()
{
	m_layout.clear();
}

void Widget::lose_focus()
{
	m_focused = false;
	m_layout.lose_focus();
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

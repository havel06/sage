#include "widget.hpp"

namespace UI
{

void Widget_Collection::add_widget(Widget_Ptr&& widget)
{
	m_widgets.push_back((Widget_Ptr&&)widget);
}

void Widget_Collection::draw(Recti parent_area, float time_delta)
{
	for (int i = 0; i < m_widgets.size(); i++) {
		m_widgets[i]->draw(parent_area, time_delta);
	}
}

void Widget::add_child(Widget_Ptr&& widget)
{
	m_children.add_widget((Widget_Ptr&&)widget);
}

void Widget::draw(Recti parent_area, float time_delta)
{
	draw_impl(parent_area, time_delta);
	m_children.draw(parent_area, time_delta);
}

}

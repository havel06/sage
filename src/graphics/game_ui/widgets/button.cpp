#include "button.hpp"
#include "../widget.hpp"
#include "utils/log.hpp"
#include "../widget_visitor.hpp"

namespace Game_UI
{


Button::Button(Widget_Ptr&& normal, Widget_Ptr&& focused, Layout&& layout) :
	Widget((Layout&&)layout)
{
	m_content_normal = (Widget_Ptr&&)normal;
	m_content_focused = (Widget_Ptr&&)focused;
}

void Button::draw_impl(Recti parent_area, float opacity, float time_delta)
{
	m_content_focused->show(is_focused());
	m_content_normal->show(!is_focused());

	m_content_focused->draw(parent_area, opacity, time_delta);
	m_content_normal->draw(parent_area, opacity, time_delta);
}

Widget_Ptr Button::clone_impl(Layout&& layout) const
{
	return make_own_ptr<Button>(m_content_normal->clone(), m_content_focused->clone(), (Layout&&)layout);
}

void Button::process_click_impl()
{
	if (is_focused()) {
		//SG_DEBUG("Button clicked");
		on_click();
	}
}

void Button::accept_visitor(Widget_Visitor& visitor)
{
	visitor.visit_button(*this);
}

}

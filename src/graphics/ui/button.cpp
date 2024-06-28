#include "button.hpp"
#include "graphics/ui/widget.hpp"

namespace UI
{


Button::Button(Widget_Ptr&& normal, Widget_Ptr&& focused, Layout&& layout) :
	Widget((Layout&&)layout)
{
	m_content_normal = (Widget_Ptr&&)normal;
	m_content_focused = (Widget_Ptr&&)focused;
}

void Button::draw_impl(Recti parent_area, float time_delta)
{
	const bool focused = false; // FIXME	
	if (focused) {
		m_content_focused->draw(parent_area, time_delta);
	} else {
		m_content_normal->draw(parent_area, time_delta);
	}
}

Widget_Ptr Button::clone_impl(Layout&& layout) const
{
	return make_own_ptr<Button>(m_content_normal->clone(), m_content_focused->clone(), (Layout&&)layout);
}


}

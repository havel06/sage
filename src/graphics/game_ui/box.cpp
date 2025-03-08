#include "box.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"
#include "widget_visitor.hpp"

namespace Game_UI
{

Box::Box(Layout&& layout) :
	Widget((Layout&&)layout)
{
}

void Box::draw_impl(Recti parent_area, float opacity, float)
{
	DrawRectangle(
		parent_area.position.x,
		parent_area.position.y,
		parent_area.size.x,
		parent_area.size.y,
		Color {
			colour.r,
			colour.g,
			colour.b,
			(unsigned char)(colour.a * opacity)
		}
	);
}

Widget_Ptr Box::clone_impl(Layout&& layout) const
{
	Own_Ptr<Box> cloned = make_own_ptr<Box>((Layout&&)layout);
	cloned->colour = colour;
	return cloned;
}

void Box::accept_visitor(Widget_Visitor& visitor)
{
	visitor.visit_box(*this);
}

}

#include "box.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"

namespace UI
{

Box::Box(Layout&& layout) :
	Widget((Layout&&)layout)
{
}

void Box::draw_impl(Recti parent_area, float)
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
			colour.a
		}
	);
}

}

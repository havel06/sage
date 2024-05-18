#include "text.hpp"
#include "raylib/raylib.h"

namespace UI
{

Text::Text(Layout&& layout) :
	Widget((Layout&&)layout)
{
}

void Text::draw_impl(Recti parent_area, float)
{
	DrawText(text.data(), parent_area.position.x, parent_area.position.y, size, WHITE);
}

}

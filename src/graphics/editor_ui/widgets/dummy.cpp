#include "dummy.hpp"

namespace Editor_UI::Widgets
{

void Dummy::draw(const Theme&, float)
{
}

void Dummy::draw_overlay(const Theme&, float)
{
}

Vec2i Dummy::layout(const Theme&, Recti)
{
	return {0, 0};
}

}

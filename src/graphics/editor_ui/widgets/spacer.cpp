#include "spacer.hpp"
#include "utils/move.hpp"
#include "utils/minmax.hpp"

namespace Editor_UI::Widgets
{

Spacer::Spacer(Vec2i size)
{
	m_size =  size;
}

void Spacer::draw(const Theme& theme, float dt)
{
	(void)theme;
	(void)dt;
}

void Spacer::draw_overlay(const Theme& theme, float dt)
{
	(void)theme;
	(void)dt;
}

Vec2i Spacer::layout(const Theme& theme, Recti bounding_box)
{
	(void)theme;
	(void)bounding_box;

	return m_size;
}

}

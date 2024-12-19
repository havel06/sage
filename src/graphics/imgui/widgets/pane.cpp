#include "pane.hpp"
#include "../theme.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"
#include <raylib/raylib.h>

namespace IMGUI::Widgets
{

Pane::Pane(Recti transform)
{
	m_transform = transform;
}

void Pane::draw()
{
	DrawRectangle(
		m_transform.position.x,
		m_transform.position.y,
		m_transform.size.x,
		m_transform.size.y,
		Color {
			.r = Theme::SURFACE.r,
			.g = Theme::SURFACE.g,
			.b = Theme::SURFACE.b,
			.a = Theme::SURFACE.a
		}
	);

	column.draw();
}

Vec2i Pane::layout(Recti bounding_box)
{
	// NOTE - bounding_box is ignored, since panes are positioned absolutely
	(void)bounding_box;
	column.layout(m_transform);
	return m_transform.size;
}

}

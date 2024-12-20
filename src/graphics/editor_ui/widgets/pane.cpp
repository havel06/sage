#include "pane.hpp"
#include "../theme.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"
#include <raylib/raylib.h>

namespace Editor_UI::Widgets
{

Pane::Pane(Recti transform, bool padding)
{
	m_transform = transform;
	m_padding = padding;
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

	const int padding = m_padding ? Theme::PADDING_DEFAULT : 0;
	const Recti children_bounding_box = {
		.position = {
			m_transform.position.x + padding,
			m_transform.position.y + padding,
		},
		.size = {
			m_transform.size.x - 2 * padding,
			m_transform.size.y - 2 * padding,
		}
	};

	column.layout(children_bounding_box);
	return m_transform.size;
}

}

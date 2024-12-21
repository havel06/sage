#include "pane.hpp"
#include "../theme.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"
#include <raylib/raylib.h>

namespace Editor_UI::Widgets
{

Pane::Pane(Recti transform, bool padding)
{
	this->transform = transform;
	m_padding = padding;
}

void Pane::draw()
{
	DrawRectangle(
		transform.position.x,
		transform.position.y,
		transform.size.x,
		transform.size.y,
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
			transform.position.x + padding,
			transform.position.y + padding,
		},
		.size = {
			transform.size.x - 2 * padding,
			transform.size.y - 2 * padding,
		}
	};

	column.layout(children_bounding_box);
	return transform.size;
}

void Pane::handle_mouse(Vec2i position, bool click)
{
	(void)position;
	(void)click;
	column.handle_mouse(position, click);
}

}

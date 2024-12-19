#include "button.hpp"
#include "utils/log.hpp"
#include "utils/minmax.hpp"
#include "../theme.hpp"
#include <raylib/raylib.h>

namespace IMGUI::Widgets
{

void Button::draw()
{
	const int corner_radius = 20;
	const int segments = 10;

	SG_DEBUG("Draw button %d %d %d %d",
		m_bounding_box.position.x,
		m_bounding_box.position.y,
		m_bounding_box.size.x,
		m_bounding_box.size.y
	);
	DrawRectangleRounded(
		Rectangle{
			(float)m_bounding_box.position.x,
			(float)m_bounding_box.position.y,
			(float)m_bounding_box.size.x,
			(float)m_bounding_box.size.y
		},
		corner_radius,
		segments,
		Color {
			Theme::PRIMARY.r,
			Theme::PRIMARY.g,
			Theme::PRIMARY.b,
			Theme::PRIMARY.a,
		}
	);
}

Vec2i Button::layout(Recti bounding_box)
{
	SG_DEBUG("Layout button %d %d %d %d",
		bounding_box.position.x,
		bounding_box.position.y,
		bounding_box.size.x,
		bounding_box.size.y
	);

	const int min_width = 40;
	const int min_height = 40;
	const int padding_vertical = 10;
	const int padding_horizontal = 24;

	// FIXME - account for padding before layout
	Vec2i child_size = row.layout(bounding_box);

	// Calculate bounding box
	m_bounding_box = Recti {
		.position = bounding_box.position,
		.size = {
			.x = max(child_size.x + 2 * padding_horizontal, min_width),
			.y = max(child_size.y + 2 * padding_vertical, min_height),
		}
	};

	return m_bounding_box.size;
}

}

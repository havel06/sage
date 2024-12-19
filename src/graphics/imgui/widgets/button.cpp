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

	row.draw();
}

Vec2i Button::layout(Recti bounding_box)
{
	const int min_width = 40;
	const int min_height = 40;
	const int padding_vertical = 10;
	const int padding_horizontal = 24;

	const Recti children_bounding_box = {
		.position = {
			bounding_box.position.x + padding_horizontal,
			bounding_box.position.y + padding_vertical,
		},
		.size = {
			bounding_box.size.x - 2 * padding_horizontal,
			bounding_box.size.y - 2 * padding_vertical,
		}
	};
	Vec2i child_size = row.layout(children_bounding_box);

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

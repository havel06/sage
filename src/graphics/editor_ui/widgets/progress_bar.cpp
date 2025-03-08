#include "progress_bar.hpp"
#include "raylib/raylib.h"
#include "../theme.hpp"

static const int THICKNESS = 4;

namespace Editor_UI::Widgets
{

void Progress_Bar::set_progress(float value)
{
	if (value < 0)
		value = 0;
	else if (value > 1)
		value = 1;

	m_progress = value;
}

Progress_Bar::Progress_Bar(float value)
{
	set_progress(value);
}

void Progress_Bar::draw(const Theme& theme, float dt)
{
	(void)dt;
	const int active_width = m_width * m_progress; // Including padding
	const int gap = THICKNESS;

	// Active indicator
	{
		const int indicator_width = active_width - gap / 2;
		DrawRectangleRounded(
			{(float)m_position.x, (float)m_position.y, (float)indicator_width, THICKNESS},
			(float)THICKNESS / 2,
			3,
			theme.PRIMARY.to_ray_color()
		);
	}

	// Track
	{
		const int track_pos_x = m_position.x + active_width + gap/2;
		const int track_width = m_width - active_width - gap/2;

		DrawRectangleRounded(
			{(float)track_pos_x, (float)m_position.y, (float)track_width, THICKNESS},
			(float)THICKNESS / 2,
			3,
			theme.SECONDARY_CONTAINER.to_ray_color()
		);
	}
}

Vec2i Progress_Bar::layout(const Theme& theme, Recti bounding_box)
{
	(void)theme;
	m_width = bounding_box.size.x;
	m_position = bounding_box.position;
	return {m_width, THICKNESS};
}

}

#include "input.hpp"
#include "../theme.hpp"
#include <raylib/raylib.h>

namespace Editor_UI::Widgets
{

Input::Input(const Font& font, const String& label) :
	m_font{font}
{
	m_label = label;
}

void Input::draw()
{
	const int segments = 4;
	const int radius = 4;

	// Draw outline
	DrawRectangleRoundedLines(
		Rectangle{
			(float)m_bounding_box.position.x,
			(float)m_bounding_box.position.y,
			(float)m_bounding_box.size.x,
			(float)m_bounding_box.size.y
		},
		radius,
		segments,
		1,
		Color {
			.r = Theme::OUTLINE.r,
			.g = Theme::OUTLINE.g,
			.b = Theme::OUTLINE.b,
			.a = Theme::OUTLINE.a,
		}
	);

	const int padding_left = 16;
	// Draw label
	if (m_active || !content.empty()) {
		const int font_size = 14;
		const int label_pos_y = m_bounding_box.position.y - font_size / 2;
		const int width = MeasureTextEx(m_font, m_label.data(), font_size, 0).x;
		DrawRectangle(
			m_bounding_box.position.x + padding_left - 2, // Extra padding
			m_bounding_box.position.y - font_size / 2,
			width + 4, // Extra padding
			font_size,
			Color {
				.r = Theme::SURFACE.r,
				.g = Theme::SURFACE.g,
				.b = Theme::SURFACE.b,
				.a = Theme::SURFACE.a,
			}
		);
		DrawTextEx(
			m_font,
			m_label.data(),
			Vector2{
				(float)m_bounding_box.position.x + padding_left,
				(float)label_pos_y,
			},
			font_size,
			0,
			Color {
				.r = Theme::ON_SURFACE.r,
				.g = Theme::ON_SURFACE.g,
				.b = Theme::ON_SURFACE.b,
				.a = Theme::ON_SURFACE.a,
			}
		);
	} else {
		const int padding_top = (48 - Theme::FONT_SIZE_DEFAULT) / 2;
		DrawTextEx(
			m_font,
			m_label.data(),
			Vector2 {
				(float)m_bounding_box.position.x + padding_left,
				(float)m_bounding_box.position.y + padding_top,
			},
			Theme::FONT_SIZE_DEFAULT,
			0,
			Color {
				.r = Theme::ON_SURFACE.r,
				.g = Theme::ON_SURFACE.g,
				.b = Theme::ON_SURFACE.b,
				.a = Theme::ON_SURFACE.a,
			}
		);
	}

	// Draw content
	// FIXME - duplicate code with label drawing
	const int padding_top = (48 - Theme::FONT_SIZE_DEFAULT) / 2;
	DrawTextEx(
		m_font,
		content.data(),
		Vector2 {
			(float)m_bounding_box.position.x + padding_left,
			(float)m_bounding_box.position.y + padding_top,
		},
		Theme::FONT_SIZE_DEFAULT,
		0,
		Color {
			.r = Theme::ON_SURFACE.r,
			.g = Theme::ON_SURFACE.g,
			.b = Theme::ON_SURFACE.b,
			.a = Theme::ON_SURFACE.a,
		}
	);
}

Vec2i Input::layout(Recti bounding_box)
{
	m_bounding_box = Recti{
		.position = bounding_box.position,
		.size = Vec2i{
			.x = bounding_box.size.x,
			.y = 48
		}
	};

	return m_bounding_box.size;
}

void Input::handle_mouse(Vec2i position, bool click)
{
	(void)position;
	(void)click;
	// FIXME
}

}

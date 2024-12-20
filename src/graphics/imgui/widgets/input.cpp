#include "input.hpp"
#include "graphics/imgui/theme.hpp"
#include <raylib/raylib.h>

namespace IMGUI::Widgets
{

Input::Input(const String& label, String& content, bool active) :
	m_content{content}
{
	m_label = label;
	m_active = active;
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
	if (m_active || !m_content.empty()) {
		const int font_size = 12;
		const int label_pos_y = m_bounding_box.position.y - font_size / 2;
		const int width = MeasureText(m_label.data(), font_size);
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
		DrawText(
			m_label.data(),
			m_bounding_box.position.x + padding_left,
			label_pos_y,
			font_size,
			Color {
				.r = Theme::ON_SURFACE.r,
				.g = Theme::ON_SURFACE.g,
				.b = Theme::ON_SURFACE.b,
				.a = Theme::ON_SURFACE.a,
			}
		);
	} else {
		const int padding_top = (48 - Theme::FONT_SIZE_DEFAULT) / 2;
		DrawText(
			m_label.data(),
			m_bounding_box.position.x + padding_left,
			m_bounding_box.position.y + padding_top,
			Theme::FONT_SIZE_DEFAULT,
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
	DrawText(
		m_content.data(),
		m_bounding_box.position.x + padding_left,
		m_bounding_box.position.y + padding_top,
		Theme::FONT_SIZE_DEFAULT,
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

}

#include "button.hpp"
#include "utils/log.hpp"
#include "utils/minmax.hpp"
#include "../theme.hpp"
#include "../icon_resource.hpp"
#include <raylib/raylib.h>

namespace Editor_UI::Widgets
{

Button::Button(const Font& font, const String& label, const Icon_Resource* icon) :
	m_font{font}
{
	m_label = label;
	m_icon = icon;
}

void Button::draw()
{
	const int corner_radius = 20;
	const int segments = 10;

	// Background
	Colour background_colour = m_hover ? Theme::PRIMARY_BUTTON_HOVER : Theme::PRIMARY;
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
			background_colour.r,
			background_colour.g,
			background_colour.b,
			background_colour.a,
		}
	);

	// Content
	const int padding_horizontal = 24;
	int x = m_bounding_box.position.x + padding_horizontal;
	if (m_icon) {
		const int icon_padding_top = (40 - Theme::ICON_SIZE) / 2;
		DrawTexture(
			m_icon->get(),
			x,
			m_bounding_box.position.y + icon_padding_top,
			Color {
				Theme::ON_PRIMARY.r,
				Theme::ON_PRIMARY.g,
				Theme::ON_PRIMARY.b,
				Theme::ON_PRIMARY.a,
			}
		);
		x += Theme::ICON_SIZE + 8;
	}
	
	const int label_padding_top = (40 - Theme::FONT_SIZE_DEFAULT) / 2;
	DrawTextEx(
		m_font,
		m_label.data(),
		{(float)x, (float)m_bounding_box.position.y + label_padding_top},
		Theme::FONT_SIZE_DEFAULT,
		0,
		Color {
			Theme::ON_PRIMARY.r,
			Theme::ON_PRIMARY.g,
			Theme::ON_PRIMARY.b,
			Theme::ON_PRIMARY.a,
		}
	);
}

Vec2i Button::layout(Recti bounding_box)
{
	const int min_width = 40;
	const int height = 40;
	const int padding_horizontal = 24;

	const int label_width = MeasureTextEx(m_font, m_label.data(), Theme::FONT_SIZE_DEFAULT, 0).x;
	const int content_width =
		m_icon ?
			label_width + Theme::PADDING_DEFAULT + Theme::PADDING_DEFAULT :
			label_width;

	// Calculate bounding box
	m_bounding_box = Recti {
		.position = bounding_box.position,
		.size = {
			.x = max(content_width + 2 * padding_horizontal, min_width),
			.y = height
		}
	};

	return m_bounding_box.size;
}

void Button::handle_mouse(Vec2i position, bool click)
{
	m_hover = m_bounding_box.contains(position);
	if (m_hover && click) {
		callback();
	}
}

}

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

void Button::draw(float dt)
{
	(void)dt;

	const int corner_radius = 20;
	const int segments = 10;

	// Background
	Colour background_colour = get_background_colour();

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
	//const Colour content_colour = transparent ? Theme::ON_SURFACE : Theme::ON_PRIMARY;
	const Colour content_colour = transparent ? Theme::ON_SURFACE : Theme::ON_PRIMARY;
	const int padding_horizontal = get_horizontal_padding();
	int x = m_bounding_box.position.x + padding_horizontal;
	if (m_icon) {
		const int icon_padding_top = (40 - Theme::ICON_SIZE) / 2;
		DrawTexture(
			m_icon->get(),
			x,
			m_bounding_box.position.y + icon_padding_top,
			Color {
				content_colour.r,
				content_colour.g,
				content_colour.b,
				content_colour.a,
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
			content_colour.r,
			content_colour.g,
			content_colour.b,
			content_colour.a,
		}
	);
}

Vec2i Button::layout(Recti bounding_box)
{
	const int min_width = 40;
	const int height = 40;
	const int padding_horizontal = get_horizontal_padding();

	const int label_width = MeasureTextEx(m_font, m_label.data(), Theme::FONT_SIZE_DEFAULT, 0).x;
	const int content_width = [&](){
		if (m_icon) {
			if (m_label.empty()) {
				return Theme::ICON_SIZE;
			} else {
				return label_width + Theme::ICON_SIZE + 8;
			}
		} else {
			return label_width;
		}
	}();

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

int Button::get_horizontal_padding()
{
	if (narrow)
		return 8;
	else
		return 24;
}

void Button::handle_mouse(Vec2i position, bool click)
{
	m_hover = m_bounding_box.contains(position);

	if (m_hover) {
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	}

	if (m_hover && click) {
		callback();
	}
}

Colour Button::get_background_colour()
{
	if (transparent) {
		if (m_hover)
			return Theme::TRANSPARENT_BUTTON_HOVER;
		else
			return Colour{0, 0, 0, 0};
	} else {
		if (m_hover)
			return Theme::FILLED_BUTTON_HOVER;
		else
			return Theme::PRIMARY;
	}
}

}

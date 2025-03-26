#include "nav_rail.hpp"
#include "../theme.hpp"
#include "raylib/raylib.h"
#include "utils/move.hpp"
#include "utils/log.hpp"
#include "utils/minmax.hpp"

namespace Editor_UI::Widgets
{

Nav_Rail_Item::Nav_Rail_Item(const Font& font, const Icon_Resource& icon, const String& label) :
	m_font{font},
	m_icon{icon},
	m_label{label}
{
}

void Nav_Rail_Item::layout(const Theme& theme)
{
	m_width = calculate_width(theme);
}

int Nav_Rail_Item::calculate_width(const Theme& theme) const
{
	const int min_width = 80;
	const int label_padding_left = 16;
	const int label_width = MeasureText(m_label.data(), theme.FONT_SIZE_DEFAULT);

	return max(min_width, label_width + 2 * label_padding_left);
}

void Nav_Rail_Item::draw(const Theme& theme, bool active)
{
	const int gap = 4;
	const int icon_padding_left = (m_width - theme.ICON_SIZE) / 2;

	if (m_hover || active) {
		// Draw icon background highlight
		const int highlight_padding_left = icon_padding_left - 16;
		DrawRectangleRounded(
			Rectangle{
				(float)position.x + highlight_padding_left,
				(float)position.y,
				56,
				(float)theme.ICON_SIZE
			},
			(float)56 / 2,
			8,
			Color {
				.r = theme.SECONDARY_CONTAINER.r,
				.g = theme.SECONDARY_CONTAINER.g,
				.b = theme.SECONDARY_CONTAINER.b,
				.a = theme.SECONDARY_CONTAINER.a,
			}
		);
	}
	
	// Draw icon
	DrawTexturePro(
		m_icon.get(),
		{0, 0, (float)theme.ICON_SIZE, (float)theme.ICON_SIZE},
		{(float)position.x + icon_padding_left, (float)position.y, (float)theme.ICON_SIZE, (float)theme.ICON_SIZE},
		{0, 0},
		0,
		Color {
			theme.ON_SURFACE.r,
			theme.ON_SURFACE.g,
			theme.ON_SURFACE.b,
			theme.ON_SURFACE.a,
		}
	);
	
	// Draw label
	const int label_width = MeasureTextEx(m_font, m_label.data(), theme.FONT_SIZE_DEFAULT, 0).x;
	const int label_padding_left = (m_width - label_width) / 2;
	const int label_pos_y = position.y + theme.ICON_SIZE + gap;
	DrawTextEx(
		m_font,
		m_label.data(),
		Vector2 {
			(float)position.x + label_padding_left,
			(float)label_pos_y,
		},
		theme.FONT_SIZE_DEFAULT,
		0,
		Color {
			.r = theme.ON_SURFACE.r,
			.g = theme.ON_SURFACE.g,
			.b = theme.ON_SURFACE.b,
			.a = theme.ON_SURFACE.a,
		}
	);
}

bool Nav_Rail_Item::handle_mouse(Vec2i mouse_position, bool click)
{
	Recti bounding_box = {
		position,
		Vec2i{m_width, 52}
	};

	m_hover = bounding_box.contains(mouse_position);

	if (m_hover) {
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
	}

	if (m_hover && click) {
		return true;
	}

	return false;
}

Nav_Rail::Nav_Rail(Function_Wrapper<void(int)>&& callback) :
	m_callback{move(callback)}
{
}

void Nav_Rail::add_item(Own_Ptr<Nav_Rail_Item>&& item)
{
	m_items.push_back(move(item));
}

void Nav_Rail::draw(const Theme& theme, float dt)
{
	(void)dt;
	// Draw background
	DrawRectangle(
		m_bounding_box.position.x,
		m_bounding_box.position.y,
		m_bounding_box.size.x,
		m_bounding_box.size.y,
		Color {
			.r = theme.SURFACE.r,
			.g = theme.SURFACE.g,
			.b = theme.SURFACE.b,
			.a = theme.SURFACE.a,
		}
	);

	for (int i = 0; i < m_items.size(); i++) {
		m_items[i]->draw(theme, m_index_active == i);
	}
}

Vec2i Nav_Rail::layout(const Theme& theme, Recti bounding_box)
{
	// Calculate width
	int width = theme.NAV_WIDTH;
	for (auto& item : m_items) {
		width = max(width, item->get_width());
	}

	// Layout children
	const int item_height = 52;
	const int gap = 16;
	const int padding_top = 16;

	int y = m_bounding_box.position.y + padding_top;

	for (auto& item : m_items) {
		item->layout(theme);
		const int padding_left = (width - item->get_width()) / 2;
		item->position = Vec2i{m_bounding_box.position.x + padding_left, y};
		y += item_height + gap;
	}
	
	// Set self bounding box
	m_bounding_box = {
		.position = bounding_box.position,
		.size = {width, bounding_box.size.y}
	};

	return m_bounding_box.size;
}

void Nav_Rail::handle_mouse(Vec2i position, bool click)
{
	//if (!m_bounding_box.contains(position))
	//	return;

	for (int i = 0; i < m_items.size(); i++) {
		if (m_items[i]->handle_mouse(position, click)) {
			set_active_index(i);
			m_callback(i);
		}
	}
}

void Nav_Rail::set_active_index(int index)
{
	m_index_active = index;
}

}

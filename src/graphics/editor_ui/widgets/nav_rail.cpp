#include "nav_rail.hpp"
#include "../theme.hpp"
#include "raylib/raylib.h"
#include "utils/move.hpp"
#include "utils/log.hpp"
#include "utils/minmax.hpp"

namespace Editor_UI::Widgets
{

Nav_Rail_Item::Nav_Rail_Item(const Font& font, const Icon_Resource& icon, const String& label, Callback&& callback) :
	m_font{font},
	m_icon{icon},
	m_label{label},
	m_callback{move(callback)}
{
}

int Nav_Rail_Item::get_width() const
{
	const int min_width = 80;
	const int label_padding_left = 16;
	const int label_width = MeasureText(m_label.data(), Theme::FONT_SIZE_DEFAULT);

	return max(min_width, label_width + 2 * label_padding_left);
}

void Nav_Rail_Item::draw(bool active)
{
	const int gap = 4;
	const int width = get_width();
	const int icon_padding_left = (width - Theme::ICON_SIZE) / 2;

	if (m_hover || active) {
		// Draw icon background highlight
		const int highlight_padding_left = icon_padding_left - 16;
		DrawRectangleRounded(
			Rectangle{
				(float)position.x + highlight_padding_left,
				(float)position.y,
				56,
				Theme::ICON_SIZE
			},
			(float)56 / 2,
			8,
			Color {
				.r = Theme::SECONDARY_CONTAINER.r,
				.g = Theme::SECONDARY_CONTAINER.g,
				.b = Theme::SECONDARY_CONTAINER.b,
				.a = Theme::SECONDARY_CONTAINER.a,
			}
		);
	}
	
	// Draw icon
	DrawTexturePro(
		m_icon.get(),
		{0, 0, Theme::ICON_SIZE, Theme::ICON_SIZE},
		{(float)position.x + icon_padding_left, (float)position.y, Theme::ICON_SIZE, Theme::ICON_SIZE},
		{0, 0},
		0,
		Color {
			Theme::ON_SURFACE.r,
			Theme::ON_SURFACE.g,
			Theme::ON_SURFACE.b,
			Theme::ON_SURFACE.a,
		}
	);
	
	// Draw label
	const int label_width = MeasureTextEx(m_font, m_label.data(), Theme::FONT_SIZE_DEFAULT, 0).x;
	const int label_padding_left = (width - label_width) / 2;
	const int label_pos_y = position.y + Theme::ICON_SIZE + gap;
	DrawTextEx(
		m_font,
		m_label.data(),
		Vector2 {
			(float)position.x + label_padding_left,
			(float)label_pos_y,
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

void Nav_Rail_Item::handle_mouse(Vec2i mouse_position, bool click)
{
	Recti bounding_box = {
		position,
		Vec2i{get_width(), 52}
	};

	m_hover = bounding_box.contains(mouse_position);
	if (m_hover && click) {
		m_callback();
	}
}

void Nav_Rail::add_item(Own_Ptr<Nav_Rail_Item>&& item)
{
	m_items.push_back(move(item));
}

void Nav_Rail::draw()
{
	// Draw background
	DrawRectangle(
		m_bounding_box.position.x,
		m_bounding_box.position.y,
		m_bounding_box.size.x,
		m_bounding_box.size.y,
		Color {
			.r = Theme::SURFACE.r,
			.g = Theme::SURFACE.g,
			.b = Theme::SURFACE.b,
			.a = Theme::SURFACE.a,
		}
	);

	for (int i = 0; i < m_items.size(); i++) {
		m_items[i]->draw(m_index_active == i);
	}
}

Vec2i Nav_Rail::layout(Recti bounding_box)
{
	// Calculate width
	int width = Theme::NAV_WIDTH;
	for (auto& item : m_items) {
		width = max(width, item->get_width());
	}

	// Layout children
	const int item_height = 52;
	const int gap = 16;
	const int padding_top = 16;

	int y = m_bounding_box.position.y + padding_top;

	for (auto& item : m_items) {
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

	for (auto& item : m_items) {
		item->handle_mouse(position, click);
	}
}

void Nav_Rail::set_active_index(int index)
{
	m_index_active = index;
}

}

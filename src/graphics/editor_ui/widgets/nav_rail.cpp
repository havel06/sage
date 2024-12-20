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

int Nav_Rail_Item::get_width() const
{
	const int min_width = 80;
	const int label_padding_left = 16;
	const int label_width = MeasureText(m_label.data(), Theme::FONT_SIZE_DEFAULT);

	return max(min_width, label_width + 2 * label_padding_left);
}

void Nav_Rail_Item::draw(Vec2i position, int width)
{
	const int gap = 4;
	//const int padding_horizontal = 16;
	const int icon_padding_left = (width - Theme::ICON_SIZE) / 2;
	
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

	const int item_height = 52;
	const int gap = 16;
	const int padding_top = 8;

	int y = m_bounding_box.position.y + padding_top;

	for (auto& item : m_items) {
		item->draw(Vec2i{m_bounding_box.position.x, y}, m_bounding_box.size.x);
		y += item_height + gap;
	}
}

Vec2i Nav_Rail::layout(Recti bounding_box)
{
	// Calculate width
	int width = Theme::NAV_WIDTH;
	for (auto& item : m_items) {
		width = max(width, item->get_width());
	}

	m_bounding_box = {
		.position = bounding_box.position,
		.size = {width, bounding_box.size.y}
	};

	return m_bounding_box.size;
}


}

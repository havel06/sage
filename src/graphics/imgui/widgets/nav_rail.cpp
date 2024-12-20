#include "nav_rail.hpp"
#include "graphics/imgui/theme.hpp"
#include "raylib/raylib.h"
#include "utils/move.hpp"
#include "utils/log.hpp"

namespace IMGUI::Widgets
{

Nav_Rail_Item::Nav_Rail_Item(const Icon_Resource& icon, const String& label) :
	m_icon{icon},
	m_label{label}
{
}

void Nav_Rail_Item::draw(Vec2i position)
{
	const int gap = 4;
	const int width = 80;
	//const int padding_horizontal = 16;
	const int icon_padding_left = 28;
	
	// Draw icon
	DrawTexturePro(
		m_icon.get(),
		{(float)m_icon.get().width, (float)m_icon.get().height, Theme::ICON_SIZE, Theme::ICON_SIZE},
		{(float)position.x + icon_padding_left, (float)position.y, Theme::ICON_SIZE, Theme::ICON_SIZE},
		{0, 0},
		0,
		WHITE
	);
	
	// Draw label
	const int label_width = MeasureText(m_label.data(), Theme::FONT_SIZE_DEFAULT);
	const int label_padding_left = (width - label_width) / 2;
	const int label_pos_y = position.y + Theme::ICON_SIZE + gap;
	DrawText(
		m_label.data(),
		position.x + label_padding_left,
		label_pos_y,
		Theme::FONT_SIZE_DEFAULT,
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
		m_position.x,
		m_position.y,
		80,
		GetScreenHeight(),
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

	int y = m_position.y + padding_top;

	for (auto& item : m_items) {
		item->draw(Vec2i{m_position.x, y});
		y += item_height + gap;
	}
}

Vec2i Nav_Rail::layout(Recti bounding_box)
{
	// FIXME - Adjustable height?
	
	m_position = bounding_box.position;
	return Vec2i{80, GetScreenHeight()};
}


}

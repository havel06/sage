#include "card.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "raylib/raylib.h"
#include "utils/rect.hpp"
#include "utils/minmax.hpp"

namespace Editor_UI::Widgets
{

Card::Card(Card_Type type)
{
	this->type = type;
}

void Card::update()
{
	column.update();
}

void Card::draw(float dt)
{
	const float border_radius = 24;
	const float roundness = border_radius / min(m_bounding_box.size.x, m_bounding_box.size.y);

	if (type == Card_Type::filled) {
		DrawRectangleRounded(
			Rectangle{
				(float)m_bounding_box.position.x,
				(float)m_bounding_box.position.y,
				(float)m_bounding_box.size.x,
				(float)m_bounding_box.size.y,
			},
			roundness,
			4,
			Theme::SURFACE_CONTAINER_HIGHEST.to_ray_color()
		);
	} else {
		DrawRectangleRoundedLines(
			Rectangle{
				(float)m_bounding_box.position.x,
				(float)m_bounding_box.position.y,
				(float)m_bounding_box.size.x,
				(float)m_bounding_box.size.y,
			},
			roundness,
			4,
			1,
			Theme::OUTLINE_VARIANT.to_ray_color()
		);
	}

	column.draw(dt);
}

Vec2i Card::layout(Recti bounding_box)
{
	Recti child_bounding_box = Recti{
		.position = {
			.x = bounding_box.position.x + Theme::PADDING_DEFAULT,
			.y = bounding_box.position.y + Theme::PADDING_DEFAULT,
		},
		.size = {
			.x = bounding_box.size.x - 2 * Theme::PADDING_DEFAULT,
			.y = bounding_box.size.y - 2 * Theme::PADDING_DEFAULT,
		}
	};

	Vec2i child_size = column.layout(child_bounding_box);
	Vec2i size = Vec2i {
		.x = child_size.x + 2 * Theme::PADDING_DEFAULT,
		.y = child_size.y + 2 * Theme::PADDING_DEFAULT
	};

	m_bounding_box = {bounding_box.position, size};

	return size;
}

void Card::handle_mouse(Vec2i position, bool click)
{
	column.handle_mouse(position, click);
}

void Card::handle_character(char character)
{
	column.handle_character(character);
}

void Card::handle_key(int key)
{
	column.handle_scroll(key);
}

void Card::handle_scroll(float amount)
{
	column.handle_scroll(amount);
}

}

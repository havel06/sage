#include "column.hpp"
#include "utils/minmax.hpp"
#include "utils/move.hpp"
#include "../theme.hpp"

namespace Editor_UI::Widgets
{

void Column::clear()
{
	m_children.clear();
}

void Column::add_child(Own_Ptr<Widget>&& child)
{
	m_children.push_back(move(child));
}

void Column::draw(const Theme& theme, float dt)
{
	for (auto& child : m_children)
		child->draw(theme, dt);
}

void Column::draw_overlay(const Theme& theme, float dt)
{
	for (auto& child : m_children)
		child->draw_overlay(theme, dt);
}

void Column::update()
{
	for (auto& child : m_children)
		child->update();
}

Vec2i Column::layout(const Theme& theme, Recti bounding_box)
{
	int height = 0;
	int width = 0;
	const int padding_px = get_padding_px(theme);

	for (auto& child : m_children)
	{
		// Layout child
		const Recti child_transfom = {
			.position = {
				bounding_box.position.x,
				bounding_box.position.y + height
			},
			.size = {
				bounding_box.size.x,
				bounding_box.size.y - height
			},
		};
		const Vec2i child_size = child->layout(theme, child_transfom);

		width = max(width, child_size.x); // Width is maximum child width
		height += child_size.y + padding_px; // Height is the sum of children heights
	}

	return Vec2i{width, height};
}

int Column::get_padding_px(const Theme& theme)
{
	switch (padding) {
		case Column_Padding::none:
			return 0;
		case Column_Padding::small:
			return theme.PADDING_SMALL;
		case Column_Padding::normal:
			return theme.PADDING_DEFAULT;
	}
}

void Column::handle_mouse(Vec2i position, bool click)
{
	for (auto& child : m_children) {
		child->handle_mouse(position, click);
	}
}

void Column::handle_character(char character)
{
	for (auto& child : m_children) {
		child->handle_character(character);
	}
}

void Column::handle_key(int key)
{
	for (auto& child : m_children) {
		child->handle_key(key);
	}
}

void Column::handle_scroll(float amount)
{
	for (auto& child : m_children) {
		child->handle_scroll(amount);
	}
}

}

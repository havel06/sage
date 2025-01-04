#include "row.hpp"
#include "utils/minmax.hpp"
#include "utils/move.hpp"

namespace Editor_UI::Widgets
{

void Row::add_child(Own_Ptr<Widget>&& child)
{
	m_children.push_back(move(child));
}

void Row::draw(float dt)
{
	for (auto& child : m_children)
		child->draw(dt);
}

void Row::update()
{
	for (auto& child : m_children)
		child->update();
}

Vec2i Row::layout(Recti bounding_box)
{
	// FIXME - refactor (and rethink) whole layout process for this widget
	if (stretch && m_children.size() > 1)
		return layout_stretch(bounding_box);
	else
		return layout_normal(bounding_box);
}

Vec2i Row::layout_stretch(Recti bounding_box)
{
	// First, get the total width and max height of children.
	Array<Vec2i> child_sizes;
	int children_total_width = 0;

	for (auto& child : m_children)
	{
		// Layout child
		const Recti child_transfom = {
			.position = {
				bounding_box.position.x + children_total_width,
				bounding_box.position.y
			},
			.size = {
				bounding_box.size.x - children_total_width,
				bounding_box.size.y
			},
		};
		const Vec2i child_size = child->layout(child_transfom);
		child_sizes.push_back(child_size);
		children_total_width += child_size.x;
	}

	// Determine required height
	int height = 0;
	for (const auto& child_size : child_sizes) {
		height = max(height, child_size.y);
	}

	// Determine size of space between children
	const int remaining_space = (bounding_box.size.x - children_total_width);
	const int gap_width = remaining_space / (m_children.size() - 1);

	// Do a second pass, now with correct positions

	int x = 0;

	for (int i = 0; i < m_children.size(); i++)
	{
		// Layout child
		const Recti child_transfom = {
			.position = {
				bounding_box.position.x + x,
				bounding_box.position.y + (height - child_sizes[i].y) / 2
			},
			.size = {
				bounding_box.size.x - x,
				child_sizes[i].y
			},
		};
		const Vec2i child_size = m_children[i]->layout(child_transfom);

		x += child_size.x;
		x += gap_width;
	}

	return Vec2i{bounding_box.size.x, height};
}

Vec2i Row::layout_normal(Recti bounding_box)
{
	int height = 0;
	int width = 0;
	Array<Vec2i> child_sizes;

	// First pass to determine sizes
	for (auto& child : m_children)
	{
		// Layout child
		const Recti child_transfom = {
			.position = {
				bounding_box.position.x + width,
				bounding_box.position.y
			},
			.size = {
				bounding_box.size.x - width,
				bounding_box.size.y
			},
		};
		const Vec2i child_size = child->layout(child_transfom);

		child_sizes.push_back(child_size);
		height = max(height, child_size.y); // Height is maximum child height
		width += child_size.x; // Width is the sum of children widths
	}

	// Second pass for correct alignment
	width = 0;
	for (int i = 0; i < m_children.size(); i++) {
		// Layout child
		const Recti child_transfom = {
			.position = {
				bounding_box.position.x + width,
				bounding_box.position.y + (height - child_sizes[i].y) / 2
			},
			.size = {
				bounding_box.size.x - width,
				height
			},
		};
		const Vec2i child_size = m_children[i]->layout(child_transfom);

		width += child_size.x; // Width is the sum of children widths
	}


	return Vec2i{width, height};
}

void Row::handle_mouse(Vec2i position, bool click)
{
	for (auto& child : m_children) {
		child->handle_mouse(position, click);
	}
}

void Row::handle_character(char character)
{
	for (auto& child : m_children) {
		child->handle_character(character);
	}
}

void Row::handle_key(int key)
{
	for (auto& child : m_children) {
		child->handle_key(key);
	}
}

void Row::handle_scroll(float amount)
{
	for (auto& child : m_children) {
		child->handle_scroll(amount);
	}
}

}

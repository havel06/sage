#include "row.hpp"
#include "utils/minmax.hpp"
#include "utils/move.hpp"

namespace Editor_UI::Widgets
{

void Row::add_child(Own_Ptr<Widget>&& child)
{
	m_children.push_back(move(child));
}

void Row::draw()
{
	for (auto& child : m_children)
		child->draw();
}

Vec2i Row::layout(Recti bounding_box)
{
	if (stretch && m_children.size() > 1)
		return layout_stretch(bounding_box);
	else
		return layout_normal(bounding_box);
}

Vec2i Row::layout_stretch(Recti bounding_box)
{
	// First, get the total width of children.
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
		children_total_width += child_size.x;
	}

	// Determine size of space between children
	const int remaining_space = (bounding_box.size.x - children_total_width);
	const int gap_width = remaining_space / (m_children.size() - 1);

	// Do a second pass, now with correct positions

	int x = 0;
	int height = 0;

	for (auto& child : m_children)
	{
		// Layout child
		const Recti child_transfom = {
			.position = {
				bounding_box.position.x + x,
				bounding_box.position.y
			},
			.size = {
				bounding_box.size.x - x,
				bounding_box.size.y
			},
		};
		const Vec2i child_size = child->layout(child_transfom);

		height = max(height, child_size.y); // Height is maximum child height
		x += child_size.x;
		x += gap_width;
	}

	return Vec2i{bounding_box.size.x, height};
}

Vec2i Row::layout_normal(Recti bounding_box)
{
	int height = 0;
	int width = 0;

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

		height = max(height, child_size.y); // Height is maximum child height
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

}

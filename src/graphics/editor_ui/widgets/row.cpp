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

}

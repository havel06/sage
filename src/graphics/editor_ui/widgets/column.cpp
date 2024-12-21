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

void Column::draw()
{
	for (auto& child : m_children)
		child->draw();
}

Vec2i Column::layout(Recti bounding_box)
{
	const int padding = Theme::PADDING_DEFAULT;
	int height = 0;
	int width = 0;

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
		const Vec2i child_size = child->layout(child_transfom);

		width = max(width, child_size.x); // Width is maximum child width
		height += child_size.y + padding; // Height is the sum of children heights
	}

	return Vec2i{width, height};
}

void Column::handle_mouse(Vec2i position, bool click)
{
	for (auto& child : m_children) {
		child->handle_mouse(position, click);
	}
}

}

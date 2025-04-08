#include "scroll_state.hpp"
#include "utils/minmax.hpp"

namespace Editor_UI::Widgets
{

void Scroll_State::update_offset(int amount)
{
	m_offset -= amount;
}

int Scroll_State::get_offset(int child_height, int bounding_box_height)
{
	// Fix offset
	const int scroll_max = max(child_height - bounding_box_height, 0);
	m_offset = min(m_offset, scroll_max);
	m_offset = max(m_offset, 0);

	return m_offset;
}

}

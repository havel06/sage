#include "nav_rail.hpp"
#include "graphics/editor_ui/widgets/nav_rail.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Nav_Rail::Nav_Rail(Function_Wrapper<void(int)>&& callback, int selected_index) :
	m_callback{move(callback)},
	m_selected_index{selected_index}
{
}

Nav_Rail& Nav_Rail::add(const Font& font, const String& label, const Icon_Resource& icon)
{
	m_items.push_back({
		&font,
		&icon,
		label
	});

	return *this;
}

Own_Ptr<Widget> Nav_Rail::make_widget()
{
	auto nav_rail = make_own_ptr<Widgets::Nav_Rail>(Function_Wrapper<void(int)>{m_callback});

	for (Item& item : m_items) {
		nav_rail->add_item(make_own_ptr<Widgets::Nav_Rail_Item>(*item.font, *item.icon, item.label));
	}

	nav_rail->set_active_index(m_selected_index);

	return nav_rail;
}

}

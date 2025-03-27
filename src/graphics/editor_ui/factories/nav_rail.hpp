#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"
#include "utils/array.hpp"

// fwd
struct Font;
namespace Editor_UI {
	class Icon_Resource;
}

namespace Editor_UI::Factories
{

class Nav_Rail final : public Widget_Factory2
{
public:
	static Nav_Rail* make(Function_Wrapper<void(int)>&& callback, int selected_index);
	Nav_Rail(Function_Wrapper<void(int)>&& callback, int selected_index);
	Nav_Rail* add(const Font& font, const String& label, const Icon_Resource& icon); // Fluent API
	Own_Ptr<Widget> make_widget() override;
private:
	struct Item
	{
		const Font* font = nullptr;
		const Icon_Resource* icon = nullptr;
		String label;
	};

	Array<Item> m_items;
	Function_Wrapper<void(int)> m_callback;
	int m_selected_index;
};

};

#include "main_nav.hpp"
#include "graphics/editor_ui/factories/constrained_container.hpp"
#include "graphics/editor_ui/factories/relative_pane.hpp"
#include "graphics/editor_ui/factories/nav_rail.hpp"
#include "graphics/editor_ui/theme.hpp"

namespace Editor
{

Own_Ptr<Editor_UI::Widget_Factory> Main_Nav::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	auto callback = [](int){
		//m_mode = (Mode)index;
		//m_dirty = true;
	};

	// FIXME - get width from theme?
	return Constrained_Container::make(Vec2i{80, 20000},
		Relative_Pane::make(false,
			Nav_Rail::make(callback, 0)
				->add(theme.font, "General", theme.ICON_ENTITY)
				->add(theme.font, "Maps", theme.ICON_ENTITY)
				->add(theme.font, "Sequences", theme.ICON_ENTITY)
				->add(theme.font, "UI", theme.ICON_ENTITY)
				->add(theme.font, "Items", theme.ICON_ENTITY)
				->add(theme.font, "Characters", theme.ICON_ENTITY)
		)
	);
}

}

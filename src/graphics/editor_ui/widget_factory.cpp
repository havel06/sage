#include "widget_factory.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "graphics/editor_ui/widgets/icon.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "graphics/editor_ui/widgets/nav_rail.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/scroll.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "utils/move.hpp"
#include "graphics/editor_ui/widgets/image.hpp"
#include "graphics/editor_ui/widgets/progress_bar.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI
{

Widget_Factory::Widget_Factory(const Font& default_font) :
	m_font{default_font}
{
}

Own_Ptr<Widgets::Button> Widget_Factory::make_button(const String& content, const Icon_Resource* icon, Function_Wrapper<void()>&& callback)
{
	auto button = make_own_ptr<Widgets::Button>(m_font, content, icon);
	button->callback = move(callback);
	return button;
}

Own_Ptr<Widgets::Button> Widget_Factory::make_icon_button(const Icon_Resource& icon, Function_Wrapper<void()>&& callback)
{
	auto button = make_own_ptr<Widgets::Button>(m_font, "", &icon);
	button->callback = move(callback);
	button->narrow = true;
	button->transparent = true;
	return button;
}

Own_Ptr<Widgets::Column> Widget_Factory::make_column()
{
	return make_own_ptr<Widgets::Column>();
}

Own_Ptr<Widgets::Divider> Widget_Factory::make_divider()
{
	return make_own_ptr<Widgets::Divider>();
}

Own_Ptr<Widgets::Icon> Widget_Factory::make_icon(const Icon_Resource& icon)
{
	return make_own_ptr<Widgets::Icon>(icon);
}

Own_Ptr<Widgets::Image> Widget_Factory::make_image(const Sprite& sprite, Vec2i size)
{
	return make_own_ptr<Widgets::Image>(sprite, size);
}

Own_Ptr<Widgets::Input> Widget_Factory::make_input(const String& label, Colour background)
{
	auto input = make_own_ptr<Widgets::Input>(m_font, label);
	input->background = background;
	return input;
}

Own_Ptr<Widgets::Nav_Rail> Widget_Factory::make_nav_rail()
{
	return make_own_ptr<Widgets::Nav_Rail>();
}

Own_Ptr<Widgets::Nav_Rail_Item> Widget_Factory::make_nav_rail_item(const Icon_Resource& icon, const String& label, Function_Wrapper<void()>&& callback)
{
	return make_own_ptr<Widgets::Nav_Rail_Item>(m_font, icon, label, move(callback));
}

Own_Ptr<Widgets::Row> Widget_Factory::make_row(bool stretch)
{
	auto row = make_own_ptr<Widgets::Row>();
	row->stretch = stretch;
	return row;
}

Own_Ptr<Widgets::Text> Widget_Factory::make_text(const String& content)
{
	return make_own_ptr<Widgets::Text>(content, m_font, Theme::ON_SURFACE);
}

Own_Ptr<Widgets::Progress_Bar> Widget_Factory::make_progress_bar(float progress)
{
	return make_own_ptr<Widgets::Progress_Bar>(progress);
}

Own_Ptr<Widgets::Scroll> Widget_Factory::make_scroll(Own_Ptr<Widget>&& child)
{
	return make_own_ptr<Widgets::Scroll>(move(child));
}

}

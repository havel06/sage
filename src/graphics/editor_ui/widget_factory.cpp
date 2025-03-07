#include "widget_factory.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widgets/card.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
#include "graphics/editor_ui/widgets/dialog.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "graphics/editor_ui/widgets/icon.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "graphics/editor_ui/widgets/nav_rail.hpp"
#include "graphics/editor_ui/widgets/absolute_pane.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/scroll.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/view_model_holder.hpp"
#include "graphics/editor_ui/widgets/stack.hpp"
#include "utils/move.hpp"
#include "graphics/editor_ui/widgets/image.hpp"
#include "graphics/editor_ui/widgets/progress_bar.hpp"
#include "graphics/editor_ui/widgets/relative_pane.hpp"
#include "graphics/editor_ui/widgets/block.hpp"
#include "graphics/editor_ui/widgets/tooltip.hpp"
#include "graphics/editor_ui/widgets/dummy.hpp"
#include "utils/own_ptr.hpp"
#include "utils/vec2.hpp"

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

Own_Ptr<Widgets::Column> Widget_Factory::make_column(Widgets::Column_Padding padding)
{
	auto column = make_own_ptr<Widgets::Column>();
	column->padding = padding;
	return column;
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

Own_Ptr<Widgets::Input> Widget_Factory::make_input(const String& label)
{
	auto input = make_own_ptr<Widgets::Input>(m_font, label, make_own_ptr<Widgets::Input_Constraint_None>());
	return input;
}

Own_Ptr<Widgets::Input> Widget_Factory::make_input_int(const String& label)
{
	auto input = make_own_ptr<Widgets::Input>(m_font, label, make_own_ptr<Widgets::Input_Constraint_Integer>());
	return input;
}

Own_Ptr<Widgets::Input> Widget_Factory::make_input_number(const String& label)
{
	auto input = make_own_ptr<Widgets::Input>(m_font, label, make_own_ptr<Widgets::Input_Constraint_Number>());
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
	return make_own_ptr<Widgets::Text>(content, m_font);
}

Own_Ptr<Widgets::Progress_Bar> Widget_Factory::make_progress_bar(float progress)
{
	return make_own_ptr<Widgets::Progress_Bar>(progress);
}

Own_Ptr<Widgets::Scroll> Widget_Factory::make_scroll(Own_Ptr<Widget>&& child)
{
	return make_own_ptr<Widgets::Scroll>(move(child));
}

Own_Ptr<Widgets::View_Model_Holder> Widget_Factory::make_view_model_holder(View_Model& view_model)
{
	return make_own_ptr<Widgets::View_Model_Holder>(view_model);
}

Own_Ptr<Widgets::Stack> Widget_Factory::make_stack()
{
	return make_own_ptr<Widgets::Stack>();
}

Own_Ptr<Widgets::Card> Widget_Factory::make_card(Widgets::Card_Type type)
{
	return make_own_ptr<Widgets::Card>(type);
}

Own_Ptr<Widgets::Dialog> Widget_Factory::make_dialog(Vec2i size)
{
	return make_own_ptr<Widgets::Dialog>(size);
}

Own_Ptr<Widgets::Absolute_Pane> Widget_Factory::make_absolute_pane(Recti transform, bool padding)
{
	return make_own_ptr<Widgets::Absolute_Pane>(transform, padding);
}

Own_Ptr<Widgets::Relative_Pane> Widget_Factory::make_relative_pane(bool padding)
{
	return make_own_ptr<Widgets::Relative_Pane>(padding);
}

Own_Ptr<Widgets::Block> Widget_Factory::make_block(Own_Ptr<Widget>&& child, Vec2i max_size)
{
	return make_own_ptr<Widgets::Block>(move(child), max_size);
}

Own_Ptr<Widgets::Tooltip> Widget_Factory::make_tooltip(Own_Ptr<Widget>&& child, const String& text)
{
	return make_own_ptr<Widgets::Tooltip>(move(child), text, m_font);
}

Own_Ptr<Widgets::Dummy> Widget_Factory::make_dummy()
{
	return make_own_ptr<Widgets::Dummy>();
}

}

#pragma once
#include "graphics/editor_ui/widgets/card_type.hpp"
#include "graphics/editor_ui/widgets/column_padding.hpp"
#include "utils/vec2.hpp"
#include "utils/rect.hpp"
#include "theme.hpp"

// fwd
template<typename T>
class Own_Ptr;
template<typename T>
class Function_Wrapper;
struct Font;
class String;
class Sprite;
struct Colour;
namespace Editor_UI {
	class Icon_Resource;
	class Widget;
	class View_Model;
}
namespace Editor_UI::Widgets {
	class Absolute_Pane;
	class Button;
	class Block;
	class Card;
	class Column;
	class Dialog;
	class Divider;
	class Dummy;
	class Icon;
	class Image;
	class Input;
	class Nav_Rail;
	class Nav_Rail_Item;
	class Progress_Bar;
	class Relative_Pane;
	class Row;
	class Scroll;
	class Stack;
	class Text;
	class Tooltip;
	class View_Model_Holder;
}


namespace Editor_UI
{

// A utility class to make widget construction easier
class Widget_Factory
{
public:
	Widget_Factory(const Font& default_font);

	Own_Ptr<Widgets::Button> make_button(const String& content, const Icon_Resource* icon, Function_Wrapper<void()>&& callback);
	Own_Ptr<Widgets::Button> make_icon_button(const Icon_Resource& icon, Function_Wrapper<void()>&& callback); // Narrow and transparent
	Own_Ptr<Widgets::Column> make_column(Widgets::Column_Padding padding = Widgets::Column_Padding::normal);
	Own_Ptr<Widgets::Divider> make_divider();
	Own_Ptr<Widgets::Icon> make_icon(const Icon_Resource& icon);
	Own_Ptr<Widgets::Image> make_image(const Sprite& sprite, Vec2i size);
	Own_Ptr<Widgets::Input> make_input(const String& label);
	Own_Ptr<Widgets::Input> make_input_int(const String& label);
	Own_Ptr<Widgets::Input> make_input_number(const String& label);
	Own_Ptr<Widgets::Nav_Rail> make_nav_rail();
	Own_Ptr<Widgets::Nav_Rail_Item> make_nav_rail_item(const Icon_Resource& icon, const String& label, Function_Wrapper<void()>&& callback);
	Own_Ptr<Widgets::Row> make_row(bool stretch = false);
	Own_Ptr<Widgets::Text> make_text(const String& content);
	Own_Ptr<Widgets::Progress_Bar> make_progress_bar(float progress);
	Own_Ptr<Widgets::Scroll> make_scroll(Own_Ptr<Widget>&& child);
	Own_Ptr<Widgets::View_Model_Holder> make_view_model_holder(View_Model&);
	Own_Ptr<Widgets::Stack> make_stack();
	Own_Ptr<Widgets::Card> make_card(Widgets::Card_Type type);
	Own_Ptr<Widgets::Dialog> make_dialog(Vec2i size);
	Own_Ptr<Widgets::Absolute_Pane> make_absolute_pane(Recti transform, bool padding);
	Own_Ptr<Widgets::Relative_Pane> make_relative_pane(bool padding);
	Own_Ptr<Widgets::Block> make_block(Own_Ptr<Widget>&& child, Vec2i max_size);
	Own_Ptr<Widgets::Tooltip> make_tooltip(Own_Ptr<Widget>&& child, const String& text);
	Own_Ptr<Widgets::Dummy> make_dummy();
private:
	const Font& m_font;
};


}

#pragma once
#include "utils/vec2.hpp"
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
	class Button;
	class Column;
	class Divider;
	class Icon;
	class Image;
	class Input;
	class Nav_Rail;
	class Nav_Rail_Item;
	class Progress_Bar;
	class Row;
	class Scroll;
	class Stack;
	class Text;
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
	Own_Ptr<Widgets::Column> make_column();
	Own_Ptr<Widgets::Divider> make_divider();
	Own_Ptr<Widgets::Icon> make_icon(const Icon_Resource& icon);
	Own_Ptr<Widgets::Image> make_image(const Sprite& sprite, Vec2i size);
	Own_Ptr<Widgets::Input> make_input(const String& label, Colour background = Theme::SURFACE);
	Own_Ptr<Widgets::Nav_Rail> make_nav_rail();
	Own_Ptr<Widgets::Nav_Rail_Item> make_nav_rail_item(const Icon_Resource& icon, const String& label, Function_Wrapper<void()>&& callback);
	Own_Ptr<Widgets::Row> make_row(bool stretch = false);
	Own_Ptr<Widgets::Text> make_text(const String& content);
	Own_Ptr<Widgets::Progress_Bar> make_progress_bar(float progress);
	Own_Ptr<Widgets::Scroll> make_scroll(Own_Ptr<Widget>&& child);
	Own_Ptr<Widgets::View_Model_Holder> make_view_model_holder(View_Model&);
	Own_Ptr<Widgets::Stack> make_stack();
private:
	const Font& m_font;
};


}

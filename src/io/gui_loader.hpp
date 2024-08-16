#pragma once

#include "graphics/ui/widget.hpp"

// fwd
class Font_Manager;
class Texture_Manager;
namespace UI {
	class Layout;
}
namespace JSON {
	class Object_View;
	class Array_View;
}

class GUI_Loader
{
public:
	GUI_Loader(Font_Manager&, Texture_Manager&, const String& project_root);
	UI::Widget_Ptr load(const String& filename);

private:
	UI::Size parse_size(const JSON::Object_View& json);
	UI::Widget_Ptr parse_widget(const JSON::Object_View& json);
	UI::Layout parse_layout(const JSON::Object_View& json);
	void parse_widget_children(const JSON::Array_View& children, UI::Layout& layout);
	UI::Widget_Ptr create_widget_from_type_name(const String& type_name, UI::Layout&&, const JSON::Object_View& params);
	UI::Widget_Ptr parse_box(UI::Layout&&, const JSON::Object_View& params);
	UI::Widget_Ptr parse_text(UI::Layout&&, const JSON::Object_View& params);
	UI::Widget_Ptr parse_image(UI::Layout&&, const JSON::Object_View& params);
	UI::Widget_Ptr parse_button(UI::Layout&&, const JSON::Object_View& params);

	Font_Manager& m_font_manager;
	Texture_Manager& m_texture_manager;
	String m_project_root;

	UI::Widget_Ptr m_fallback_widget;
};

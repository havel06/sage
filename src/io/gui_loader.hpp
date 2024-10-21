#pragma once

#include "graphics/ui/widget.hpp"

// fwd
class Font_Manager;
class Texture_Manager;
namespace UI {
	class Layout;
	enum class Text_Align;
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
	UI::Widget_Ptr parse_widget(const JSON::Object_View& json, const JSON::Object_View& template_params);
	UI::Widget_Ptr parse_templated_widget(const JSON::Object_View& widget_json, const JSON::Object_View& template_params);
	UI::Layout parse_layout(const JSON::Object_View& json, const JSON::Object_View& template_params);
	void parse_widget_children(const JSON::Array_View& children, UI::Layout& layout, const JSON::Object_View& template_params);
	UI::Widget_Ptr create_widget_from_type_name(const String& type_name, UI::Layout&&, const JSON::Object_View& params, const JSON::Object_View& template_params);
	UI::Widget_Ptr parse_box(UI::Layout&&, const JSON::Object_View& params, const JSON::Object_View& template_params);
	UI::Widget_Ptr parse_text(UI::Layout&&, const JSON::Object_View& params, const JSON::Object_View& template_params);
	UI::Widget_Ptr parse_image(UI::Layout&&, const JSON::Object_View& params, const JSON::Object_View& template_params);
	UI::Widget_Ptr parse_button(UI::Layout&&, const JSON::Object_View& params, const JSON::Object_View& template_params);
	UI::Text_Align parse_align(const String&);

	Font_Manager& m_font_manager;
	Texture_Manager& m_texture_manager;
	String m_project_root;

	UI::Widget_Ptr m_fallback_widget;
};

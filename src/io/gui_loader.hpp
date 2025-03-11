#pragma once

#include "graphics/game_ui/widget.hpp"

// fwd
class Font_Manager;
class Texture_Manager;
namespace Game_UI {
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
	Game_UI::Widget_Ptr load(const String& filename);

private:
	Game_UI::Widget_Ptr parse_widget(const JSON::Object_View& json, const JSON::Object_View& template_params);
	Game_UI::Widget_Ptr parse_templated_widget(const JSON::Object_View& widget_json, const JSON::Object_View& template_params);
	Game_UI::Layout parse_layout(const JSON::Object_View& json, const JSON::Object_View& template_params);
	void parse_widget_children(const JSON::Array_View& children, Game_UI::Layout& layout, const JSON::Object_View& template_params);
	Game_UI::Widget_Ptr create_widget_from_type_name(const String& type_name, Game_UI::Layout&&, const JSON::Object_View& params, const JSON::Object_View& template_params);
	Game_UI::Widget_Ptr parse_box(Game_UI::Layout&&, const JSON::Object_View& params, const JSON::Object_View& template_params);
	Game_UI::Widget_Ptr parse_text(Game_UI::Layout&&, const JSON::Object_View& params, const JSON::Object_View& template_params);
	Game_UI::Widget_Ptr parse_image(Game_UI::Layout&&, const JSON::Object_View& params, const JSON::Object_View& template_params);
	Game_UI::Widget_Ptr parse_button(Game_UI::Layout&&, const JSON::Object_View& params, const JSON::Object_View& template_params);

	Font_Manager& m_font_manager;
	Texture_Manager& m_texture_manager;
	String m_project_root;

	Game_UI::Widget_Ptr m_fallback_widget;
};

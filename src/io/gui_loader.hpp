#pragma once

#include "graphics/game_ui/widget.hpp"

// fwd
class Font_Manager;
class Texture_Manager;
class Parameter_Parser;
namespace Game_UI {
	class Layout;
	enum class Text_Align;
	class Widget_Factory;
	struct Layout_Description;
}
namespace JSON {
	class Object_View;
	class Array_View;
}

class GUI_Loader
{
public:
	GUI_Loader(Font_Manager&, Parameter_Parser&, const String& project_root);
	Game_UI::Widget_Ptr load(const String& filename);

private:
	Game_UI::Widget_Ptr parse_widget(const JSON::Object_View& json, const JSON::Object_View& template_params);
	Own_Ptr<Game_UI::Widget_Factory> parse_widget_factory(const JSON::Object_View& json, const JSON::Object_View& template_params);
	Own_Ptr<Game_UI::Widget_Factory> parse_templated_widget_factory(const JSON::Object_View& widget_json, const JSON::Object_View& template_params);
	Game_UI::Layout_Description parse_layout(const JSON::Object_View& json, const JSON::Object_View& template_params);
	Array<Own_Ptr<Game_UI::Widget_Factory>> parse_widget_children(const JSON::Array_View& children, const JSON::Object_View& template_params);
	Own_Ptr<Game_UI::Widget_Factory> create_widget_from_type_name(const String& type_name);
	// FIXME - duplicate code with Event_Parser!!
	void parse_widget_parameters(Game_UI::Widget_Factory& factory,
			const JSON::Object_View& widget_parameters,
			const JSON::Object_View& template_parameters);

	Font_Manager& m_font_manager;
	Parameter_Parser& m_parameter_parser;
	String m_project_root;

	Game_UI::Widget_Ptr m_fallback_widget;
};

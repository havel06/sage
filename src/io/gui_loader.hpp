#pragma once

#include "graphics/ui/widget.hpp"

// fwd
class Font_Manager;
class Texture_Manager;
namespace JSON {
	class Object_View;
}

class GUI_Loader
{
public:
	GUI_Loader(Font_Manager&, Texture_Manager&);
	UI::Widget_Ptr load(const char* filename);

private:
	UI::Size parse_size(const JSON::Object_View& json);
	UI::Widget_Ptr parse_widget(const JSON::Object_View& json);
	UI::Layout parse_layout(const JSON::Object_View& json);
	UI::Widget_Ptr parse_box(UI::Layout&&, const JSON::Object_View& params);
	UI::Widget_Ptr parse_text(UI::Layout&&, const JSON::Object_View& params);
	UI::Widget_Ptr parse_image(UI::Layout&&, const JSON::Object_View& params);
	UI::Widget_Ptr parse_button(UI::Layout&&, const JSON::Object_View& params);

	Font_Manager& m_font_manager;
	Texture_Manager& m_texture_manager;
};

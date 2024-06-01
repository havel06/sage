#pragma once

#include "graphics/ui/widget.hpp"

// fwd
struct cJSON;
class Font_Manager;

class GUI_Loader
{
public:
	GUI_Loader(Font_Manager&);
	UI::Widget_Ptr load(const char* filename);

private:
	UI::Widget_Ptr parse_widget(const cJSON* json);
	UI::Layout parse_layout(const cJSON* json);
	UI::Widget_Ptr parse_box(UI::Layout&&, const cJSON* params);
	UI::Widget_Ptr parse_text(UI::Layout&&, const cJSON* params);

	Font_Manager& m_font_manager;
};

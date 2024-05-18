#pragma once

#include "graphics/ui/widget.hpp"

struct cJSON;

class GUI_Loader
{
public:
	UI::Widget_Ptr load(const char* filename);

private:
	UI::Widget_Ptr parse_widget(const cJSON* json);
	UI::Layout parse_layout(const cJSON* json);
	UI::Widget_Ptr parse_box(UI::Layout&&, const cJSON* params);
	UI::Widget_Ptr parse_text(UI::Layout&&, const cJSON* params);
};

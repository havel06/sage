#include "gui_loader.hpp"
#include "utils/file.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/ui/text.hpp"
#include "graphics/ui/box.hpp"
#include <cJSON.h>

UI::Widget_Ptr GUI_Loader::load(const char* filename)
{
	String file_content = read_file_to_str(filename);

	const cJSON* json = cJSON_Parse(file_content.data());

	return parse_widget(json);
}

UI::Widget_Ptr GUI_Loader::parse_widget(const cJSON* json)
{
	String type = cJSON_GetObjectItem(json, "type")->valuestring;
	const cJSON* params = cJSON_GetObjectItem(json, "parameters");

	UI::Widget_Ptr widget;
	if (type == "box") {
		widget = parse_box(params);
	} else if (type == "text") {
		widget = parse_text(params);
	} else {
		SG_ERROR("Invalid widget type \"%s\"", type.data());
		// FIXME - recover
		assert(false);
	}

	return widget;
}

UI::Widget_Ptr GUI_Loader::parse_box(const cJSON* params)
{
	Own_Ptr<UI::Box> widget = make_own_ptr<UI::Box>();

	const cJSON* colour_json = cJSON_GetObjectItem(params, "colour");
	widget->colour.r = cJSON_GetObjectItem(colour_json, "r")->valueint;
	widget->colour.g = cJSON_GetObjectItem(colour_json, "g")->valueint;
	widget->colour.b = cJSON_GetObjectItem(colour_json, "b")->valueint;
	widget->colour.a = cJSON_GetObjectItem(colour_json, "a")->valueint;

	return widget;
}

UI::Widget_Ptr GUI_Loader::parse_text(const cJSON* params)
{
	Own_Ptr<UI::Text> widget = make_own_ptr<UI::Text>();
	widget->text = cJSON_GetObjectItem(params, "text")->valuestring;
	return widget;
}

#include "gui_loader.hpp"
#include "graphics/ui/widget.hpp"
#include "utils/file.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/ui/text.hpp"
#include "graphics/ui/box.hpp"
#include "io/resource/font_manager.hpp"
#include <cJSON.h>

GUI_Loader::GUI_Loader(Font_Manager& font_mgr) :
	m_font_manager{font_mgr}
{
}

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

	// Layout
	UI::Layout layout = parse_layout(cJSON_GetObjectItem(json, "layout"));

	// Children
	// FIXME - refactor this code block to a function
	const cJSON* children = cJSON_GetObjectItem(json, "children");
	const cJSON* child;
	cJSON_ArrayForEach(child, children) {
		layout.add(UI::Layout_Element {
			.row = cJSON_GetObjectItem(child, "row")->valueint,
			.column = cJSON_GetObjectItem(child, "column")->valueint,
			.widget = parse_widget(child)
		});
	}

	// FIXME - refactor this code block to a function
	UI::Widget_Ptr widget;
	if (type == "box") {
		widget = parse_box((UI::Layout&&)layout, params);
	} else if (type == "text") {
		widget = parse_text((UI::Layout&&)layout, params);
	} else {
		SG_ERROR("Invalid widget type \"%s\"", type.data());
		// FIXME - recover
		assert(false);
	}

	// Name
	const cJSON* name_json = cJSON_GetObjectItem(json, "name");
	if (name_json) {
		widget->set_name(String{name_json->valuestring});
	}

	return widget;
}

UI::Layout GUI_Loader::parse_layout(const cJSON* json)
{
	// FIXME - what if the numbers don't add up to 100??
	Array<float> rows;
	Array<float> columns;

	const cJSON* rows_json = cJSON_GetObjectItem(json, "rows");
	const cJSON* row_json;
	cJSON_ArrayForEach(row_json, rows_json) {
		rows.push_back(row_json->valuedouble / 100);
	}

	const cJSON* columns_json = cJSON_GetObjectItem(json, "columns");
	const cJSON* column_json;
	cJSON_ArrayForEach(column_json, columns_json) {
		columns.push_back(column_json->valuedouble / 100);
	}

	return UI::Layout{rows, columns};
}

UI::Widget_Ptr GUI_Loader::parse_box(UI::Layout&& layout, const cJSON* params)
{
	Own_Ptr<UI::Box> widget = make_own_ptr<UI::Box>((UI::Layout&&)layout);

	if (params) {
		const cJSON* colour_json = cJSON_GetObjectItem(params, "colour");
		widget->colour.r = cJSON_GetObjectItem(colour_json, "r")->valueint;
		widget->colour.g = cJSON_GetObjectItem(colour_json, "g")->valueint;
		widget->colour.b = cJSON_GetObjectItem(colour_json, "b")->valueint;
		widget->colour.a = cJSON_GetObjectItem(colour_json, "a")->valueint;
	}

	return widget;
}

UI::Widget_Ptr GUI_Loader::parse_text(UI::Layout&& layout, const cJSON* params)
{
	Own_Ptr<UI::Text> widget = make_own_ptr<UI::Text>((UI::Layout&&)layout);

	if (params) {
		widget->text = cJSON_GetObjectItem(params, "text")->valuestring;
		widget->size = cJSON_GetObjectItem(params, "size")->valueint;
		widget->font = m_font_manager.get(cJSON_GetObjectItem(params, "font")->valuestring, false);
	}

	return widget;
}

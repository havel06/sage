#include "gui_loader.hpp"
#include "graphics/ui/widget.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/ui/text.hpp"
#include "graphics/ui/box.hpp"
#include "io/resource/font_manager.hpp"

GUI_Loader::GUI_Loader(Font_Manager& font_mgr) :
	m_font_manager{font_mgr}
{
}

UI::Widget_Ptr GUI_Loader::load(const char* filename)
{
	JSON::Object json = JSON::Object::from_file(filename);

	return parse_widget(json.get_view());
}

UI::Widget_Ptr GUI_Loader::parse_widget(const JSON::Object_View& json)
{
	String type = json["type"].as_string();
	JSON::Object_View params = json["parameters"].as_object();

	// Layout
	UI::Layout layout = json.has("layout") ? parse_layout(json["layout"].as_object()) : UI::Layout{};

	// Children
	// FIXME - refactor this code block to a function
	if (json.has("children")) {
		json["children"].as_array().for_each([&](const JSON::Value_View& value){
			JSON::Object_View child = value.as_object();
			if (child.has("row") && child.has("column")) {
				const int row = child["row"].as_int();
				const int column = child["column"].as_int();
				layout.add(parse_widget(child), row, column);
			} else {
				layout.add(parse_widget(child));
			}
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
	if (json.has("name")) {
		widget->set_name(json["name"].as_string());
	}

	return widget;
}

UI::Layout GUI_Loader::parse_layout(const JSON::Object_View& json)
{
	// FIXME - what if the numbers don't add up to 1??
	Array<UI::Size> rows;
	Array<UI::Size> columns;

	json["rows"].as_array().for_each([&](const JSON::Value_View& row){
		rows.push_back(UI::Size{ .parent_height = row.as_float()});
	});

	json["columns"].as_array().for_each([&](const JSON::Value_View& column){
		columns.push_back(UI::Size{ .parent_width = column.as_float()});
	});

	return UI::Layout{rows, columns};
}

UI::Widget_Ptr GUI_Loader::parse_box(UI::Layout&& layout, const JSON::Object_View& params)
{
	Own_Ptr<UI::Box> widget = make_own_ptr<UI::Box>((UI::Layout&&)layout);

	if (params.has("colour")) {
		JSON::Object_View colour_json = params["colour"].as_object();
		widget->colour.r = colour_json["r"].as_int();
		widget->colour.g = colour_json["g"].as_int();
		widget->colour.b = colour_json["b"].as_int();
		widget->colour.a = colour_json["a"].as_int();
	}

	return widget;
}

UI::Widget_Ptr GUI_Loader::parse_text(UI::Layout&& layout, const JSON::Object_View& params)
{
	Own_Ptr<UI::Text> widget = make_own_ptr<UI::Text>((UI::Layout&&)layout);

	widget->text = params["text"].as_string();
	widget->size = params["size"].as_int();
	widget->font = m_font_manager.get(params["font"].as_string(), false);

	return widget;
}

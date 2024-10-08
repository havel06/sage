#include "gui_loader.hpp"
#include "graphics/ui/button.hpp"
#include "graphics/ui/image.hpp"
#include "graphics/ui/layout.hpp"
#include "graphics/ui/widget.hpp"
#include "io/json_types.hpp"
#include "io/resource/texture_manager.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/ui/text.hpp"
#include "graphics/ui/box.hpp"
#include "io/resource/font_manager.hpp"

GUI_Loader::GUI_Loader(Font_Manager& font_mgr, Texture_Manager& tex_mgr, const String& project_root) :
	m_font_manager{font_mgr},
	m_texture_manager{tex_mgr}
{
	m_project_root = project_root;

	m_fallback_widget = make_own_ptr<UI::Box>(UI::Layout{});
}

UI::Widget_Ptr GUI_Loader::load(const String& filename)
{
	String path = m_project_root;
	path.append('/');
	path.append(filename);

	JSON::Object json = JSON::Object::from_file(path.data());

	UI::Widget_Ptr loaded_widget = parse_widget(json.get_view());

	if (loaded_widget) {
		SG_INFO("Loaded GUI widget \"%s\"", filename.data());
		return loaded_widget;
	} else {
		SG_ERROR("Couldn't load GUI widget \"%s\", using fallback instead", filename.data());
		return m_fallback_widget->clone();
	}
}

UI::Size GUI_Loader::parse_size(const JSON::Object_View& json)
{
	UI::Size size;

	if (json.has("automatic")) {
		size.automatic = json["automatic"].as_bool(false);
		return size; // We can return immediately, since other values are ignored
	}

	if (json.has("parent_width")) {
		size.parent_width = json["parent_width"].as_float(0);
	}

	if (json.has("parent_height")) {
		size.parent_height = json["parent_height"].as_float(0);
	}

	if (json.has("pixels")) {
		size.pixels = json["pixels"].as_int(0);
	}

	return size;
}

UI::Widget_Ptr GUI_Loader::parse_widget(const JSON::Object_View& json)
{
	String type = json["type"].as_string("");

	if (type.empty()) {
		SG_ERROR("Missing widget type.");
		return nullptr;
	}

	JSON::Object_View params = json["parameters"].as_object();
	// Layout
	UI::Layout layout = json.has("layout") ? parse_layout(json["layout"].as_object()) : UI::Layout{};
	// Children
	if (json.has("children"))
		parse_widget_children(json["children"].as_array(), layout);

	UI::Widget_Ptr widget = create_widget_from_type_name(type, move(layout), params);
	// Name
	if (json.has("name"))
		widget->set_name(json["name"].as_string(""));
	// Fade in
	if (json.has("fade_in"))
		widget->fade_in_out_time = json["fade_in"].as_float(1);

	return widget;
}

void GUI_Loader::parse_widget_children(const JSON::Array_View& children, UI::Layout& layout)
{
	children.for_each([&](const JSON::Value_View& value){
		JSON::Object_View child = value.as_object();
		if (child.has("row") && child.has("column")) {
			const int row = child["row"].as_int(0);
			const int column = child["column"].as_int(0);
			layout.add(parse_widget(child), row, column);
		} else {
			layout.add(parse_widget(child));
		}
	});
}

UI::Widget_Ptr GUI_Loader::create_widget_from_type_name(const String& type_name, UI::Layout&& layout, const JSON::Object_View& params)
{
	if (type_name == "box") {
		return parse_box((UI::Layout&&)layout, params);
	} else if (type_name == "text") {
		return parse_text((UI::Layout&&)layout, params);
	} else if (type_name == "image") {
		return parse_image((UI::Layout&&)layout, params);
	} else if (type_name == "button") {
		return parse_button((UI::Layout&&)layout, params);
	} else {
		SG_ERROR("Invalid widget type \"%s\"", type_name.data());
		return make_own_ptr<UI::Box>(UI::Layout{});
	}
}

UI::Layout GUI_Loader::parse_layout(const JSON::Object_View& json)
{
	// FIXME - what if the numbers don't add up to 1??
	Array<UI::Size> rows;
	Array<UI::Size> columns;

	json["rows"].as_array().for_each([&](const JSON::Value_View& row){
		rows.push_back(parse_size(row.as_object()));
	});

	json["columns"].as_array().for_each([&](const JSON::Value_View& column){
		columns.push_back(parse_size(column.as_object()));
	});

	return UI::Layout{rows, columns};
}

UI::Widget_Ptr GUI_Loader::parse_box(UI::Layout&& layout, const JSON::Object_View& params)
{
	Own_Ptr<UI::Box> widget = make_own_ptr<UI::Box>((UI::Layout&&)layout);

	if (params.has("colour")) {
		JSON::Object_View colour_json = params["colour"].as_object();
		widget->colour.r = colour_json["r"].as_int(0);
		widget->colour.g = colour_json["g"].as_int(0);
		widget->colour.b = colour_json["b"].as_int(0);
		widget->colour.a = colour_json["a"].as_int(255);
	}

	return widget;
}

UI::Widget_Ptr GUI_Loader::parse_text(UI::Layout&& layout, const JSON::Object_View& params)
{
	Resource_Handle<Font> font = m_font_manager.get(params["font"].as_string(""), false);
	Own_Ptr<UI::Text> widget = make_own_ptr<UI::Text>(font, (UI::Layout&&)layout);

	widget->text = params["text"].as_string("");
	widget->size = params["size"].as_int(16);
	if (params.has("align")) {
		widget->align = parse_align(params["align"].as_string("left"));
	}

	return widget;
}

UI::Text_Align GUI_Loader::parse_align(const String& text)
{
	if (text == "center")
		return UI::Text_Align::center;
	if (text == "left")
		return UI::Text_Align::left;

	SG_ERROR("Unknown align value \"%s\"", text.data());
	return UI::Text_Align::left;
}

UI::Widget_Ptr GUI_Loader::parse_image(UI::Layout&& layout, const JSON::Object_View& params)
{
	Own_Ptr<UI::Image> widget = make_own_ptr<UI::Image>((UI::Layout&&)layout);

	if (params.has("sprite"))
		widget->sprite = JSON_Types::parse_sprite(params["sprite"].as_object(), m_texture_manager);

	return widget;
}

UI::Widget_Ptr GUI_Loader::parse_button(UI::Layout&& layout, const JSON::Object_View& params)
{
	UI::Widget_Ptr content_normal = parse_widget(params["normal"].as_object());
	UI::Widget_Ptr content_focused = parse_widget(params["focused"].as_object());

	return make_own_ptr<UI::Button>((UI::Widget_Ptr&&)content_normal, (UI::Widget_Ptr&&)content_focused, (UI::Layout&&)layout);
}

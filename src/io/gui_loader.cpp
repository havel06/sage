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
#include "io/template.hpp"

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

	JSON::Object empty_params;
	UI::Widget_Ptr loaded_widget = parse_widget(json.get_view(), empty_params.get_view());

	if (loaded_widget) {
		SG_INFO("Loaded GUI widget \"%s\"", filename.data());
		return loaded_widget;
	} else {
		SG_ERROR("Couldn't load GUI widget \"%s\", using fallback instead", filename.data());
		return m_fallback_widget->clone();
	}
}

UI::Size GUI_Loader::parse_size(const JSON::Object_View& json, const JSON::Object_View& template_params)
{
	UI::Size size;

	if (json.has("automatic")) {
		size.automatic = resolve_templated_value(json["automatic"], template_params).as_bool(false);
		return size; // We can return immediately, since other values are ignored
	}

	if (json.has("parent_width")) {
		size.parent_width = resolve_templated_value(json["parent_width"], template_params).as_float(0);
	}

	if (json.has("parent_height")) {
		size.parent_height = resolve_templated_value(json["parent_height"], template_params).as_float(0);
	}

	if (json.has("pixels")) {
		size.pixels = resolve_templated_value(json["pixels"], template_params).as_int(0);
	}

	return size;
}

UI::Widget_Ptr GUI_Loader::parse_widget(const JSON::Object_View& json, const JSON::Object_View& template_params)
{
	if (json.has("from_template")) {
		// Use widget template
		JSON::Object_View template_spec = json["from_template"].as_object();
		String template_filename = m_project_root;
		template_filename.append('/');
		template_filename.append(template_spec["template"].as_string(""));
		JSON::Object_View params = template_spec["parameters"].as_object();

		JSON::Object template_json = JSON::Object::from_file(template_filename.data());

		SG_DEBUG("Parsing GUI widget template %s", template_filename.data());
		return parse_templated_widget(template_json.get_view(), params);
	} else {
		return parse_templated_widget(json, template_params);
	}
}

UI::Widget_Ptr GUI_Loader::parse_templated_widget(const JSON::Object_View& widget_json, const JSON::Object_View& template_params)
{
	String type = widget_json["type"].as_string("");

	if (type.empty()) {
		SG_ERROR("Missing widget type.");
		return nullptr;
	}

	JSON::Object_View params = widget_json["parameters"].as_object();
	// Layout
	UI::Layout layout = widget_json.has("layout") ? parse_layout(widget_json["layout"].as_object(), template_params) : UI::Layout{};
	// Children
	if (widget_json.has("children"))
		parse_widget_children(widget_json["children"].as_array(), layout, template_params);

	UI::Widget_Ptr widget = create_widget_from_type_name(type, move(layout), params, template_params);
	// Name
	if (widget_json.has("name"))
		widget->set_name(resolve_templated_value(widget_json["name"], template_params).as_string(""));
	// Fade in
	if (widget_json.has("fade_in"))
		widget->fade_in_out_time = resolve_templated_value(widget_json["fade_in"], template_params).as_float(1);

	return widget;
}

void GUI_Loader::parse_widget_children(const JSON::Array_View& children, UI::Layout& layout, const JSON::Object_View& template_params)
{
	children.for_each([&](const JSON::Value_View& value){
		JSON::Object_View child = resolve_templated_value(value, template_params).as_object();
		if (child.has("row") && child.has("column")) {
			const int row = child["row"].as_int(0);
			const int column = child["column"].as_int(0);
			layout.add(parse_widget(child, template_params), row, column);
		} else {
			layout.add(parse_widget(child, template_params));
		}
	});
}

UI::Widget_Ptr GUI_Loader::create_widget_from_type_name(const String& type_name, UI::Layout&& layout, const JSON::Object_View& params, const JSON::Object_View& template_params)
{
	if (type_name == "box") {
		return parse_box((UI::Layout&&)layout, params, template_params);
	} else if (type_name == "text") {
		return parse_text((UI::Layout&&)layout, params, template_params);
	} else if (type_name == "image") {
		return parse_image((UI::Layout&&)layout, params, template_params);
	} else if (type_name == "button") {
		return parse_button((UI::Layout&&)layout, params, template_params);
	} else {
		SG_ERROR("Invalid widget type \"%s\"", type_name.data());
		return make_own_ptr<UI::Box>(UI::Layout{});
	}
}

UI::Layout GUI_Loader::parse_layout(const JSON::Object_View& json, const JSON::Object_View& template_params)
{
	// FIXME - what if the numbers don't add up to 1??
	Array<UI::Size> rows;
	Array<UI::Size> columns;

	json["rows"].as_array().for_each([&](const JSON::Value_View& row){
		rows.push_back(parse_size(row.as_object(), template_params));
	});

	json["columns"].as_array().for_each([&](const JSON::Value_View& column){
		columns.push_back(parse_size(column.as_object(), template_params));
	});

	return UI::Layout{rows, columns};
}

UI::Widget_Ptr GUI_Loader::parse_box(UI::Layout&& layout, const JSON::Object_View& params, const JSON::Object_View& template_params)
{
	Own_Ptr<UI::Box> widget = make_own_ptr<UI::Box>((UI::Layout&&)layout);

	if (params.has("colour")) {
		JSON::Object_View colour_json = resolve_templated_value(params["colour"], template_params).as_object();
		widget->colour.r = resolve_templated_value(colour_json["r"], template_params).as_int(0);
		widget->colour.g = resolve_templated_value(colour_json["g"], template_params).as_int(0);
		widget->colour.b = resolve_templated_value(colour_json["b"], template_params).as_int(0);
		widget->colour.a = resolve_templated_value(colour_json["a"], template_params).as_int(255);
	}

	return widget;
}

UI::Widget_Ptr GUI_Loader::parse_text(UI::Layout&& layout, const JSON::Object_View& params, const JSON::Object_View& template_params)
{
	Resource_Handle<Font> font = m_font_manager.get(resolve_templated_value(params["font"], template_params).as_string(""), false);
	Own_Ptr<UI::Text> widget = make_own_ptr<UI::Text>(font, (UI::Layout&&)layout);

	widget->text = resolve_templated_value(params["text"], template_params).as_string("");
	widget->size = resolve_templated_value(params["size"], template_params).as_int(16);
	if (params.has("align")) {
		widget->align = parse_align(resolve_templated_value(params["align"], template_params).as_string("left"));
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

UI::Widget_Ptr GUI_Loader::parse_image(UI::Layout&& layout, const JSON::Object_View& params, const JSON::Object_View& template_params)
{
	Own_Ptr<UI::Image> widget = make_own_ptr<UI::Image>((UI::Layout&&)layout);

	if (params.has("sprite")) {
		widget->sprite = JSON_Types::parse_sprite(
			resolve_templated_value(params["sprite"], template_params).as_object(),
			m_texture_manager
		);
	}

	return widget;
}

UI::Widget_Ptr GUI_Loader::parse_button(UI::Layout&& layout, const JSON::Object_View& params, const JSON::Object_View& template_params)
{
	UI::Widget_Ptr content_normal = parse_widget(resolve_templated_value(params["normal"], template_params).as_object(), template_params);
	UI::Widget_Ptr content_focused = parse_widget(resolve_templated_value(params["focused"], template_params).as_object(), template_params);

	return make_own_ptr<UI::Button>((UI::Widget_Ptr&&)content_normal, (UI::Widget_Ptr&&)content_focused, (UI::Layout&&)layout);
}

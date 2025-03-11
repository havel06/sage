#include "gui_loader.hpp"
#include "graphics/game_ui/widgets/button.hpp"
#include "graphics/game_ui/widgets/image.hpp"
#include "graphics/game_ui/layout.hpp"
#include "graphics/game_ui/widget.hpp"
#include "io/json_types.hpp"
#include "io/resource/texture_manager.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/game_ui/widgets/text.hpp"
#include "graphics/game_ui/widgets/box.hpp"
#include "io/resource/font_manager.hpp"
#include "io/template.hpp"

GUI_Loader::GUI_Loader(Font_Manager& font_mgr, Texture_Manager& tex_mgr, const String& project_root) :
	m_font_manager{font_mgr},
	m_texture_manager{tex_mgr}
{
	m_project_root = project_root;

	m_fallback_widget = make_own_ptr<Game_UI::Box>(Game_UI::Layout{});
}

Game_UI::Widget_Ptr GUI_Loader::load(const String& filename)
{
	String path = m_project_root;
	path.append('/');
	path.append(filename);

	JSON::Object json = JSON::Object::from_file(path.data());

	JSON::Object empty_params;
	Game_UI::Widget_Ptr loaded_widget = parse_widget(json.get_view(), empty_params.get_view());

	if (loaded_widget) {
		SG_INFO("Loaded GUI widget \"%s\"", filename.data());
		return loaded_widget;
	} else {
		SG_ERROR("Couldn't load GUI widget \"%s\", using fallback instead", filename.data());
		return m_fallback_widget->clone();
	}
}


Game_UI::Widget_Ptr GUI_Loader::parse_widget(const JSON::Object_View& json, const JSON::Object_View& template_params)
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

Game_UI::Widget_Ptr GUI_Loader::parse_templated_widget(const JSON::Object_View& widget_json, const JSON::Object_View& template_params)
{
	String type = widget_json["type"].as_string("");

	if (type.empty()) {
		SG_ERROR("Missing widget type.");
		return nullptr;
	}

	JSON::Object_View params = widget_json["parameters"].as_object();
	// Layout
	Game_UI::Layout layout = widget_json.has("layout") ? parse_layout(widget_json["layout"].as_object(), template_params) : Game_UI::Layout{};
	// Children
	if (widget_json.has("children"))
		parse_widget_children(widget_json["children"].as_array(), layout, template_params);

	Game_UI::Widget_Ptr widget = create_widget_from_type_name(type, move(layout), params, template_params);
	// Name
	if (widget_json.has("name"))
		widget->set_name(resolve_templated_value(widget_json["name"], template_params).as_string(""));
	// Fade in
	if (widget_json.has("fade_in"))
		widget->fade_in_out_time = resolve_templated_value(widget_json["fade_in"], template_params).as_float(1);

	return widget;
}

void GUI_Loader::parse_widget_children(const JSON::Array_View& children, Game_UI::Layout& layout, const JSON::Object_View& template_params)
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

Game_UI::Widget_Ptr GUI_Loader::create_widget_from_type_name(const String& type_name, Game_UI::Layout&& layout, const JSON::Object_View& params, const JSON::Object_View& template_params)
{
	if (type_name == "box") {
		return parse_box((Game_UI::Layout&&)layout, params, template_params);
	} else if (type_name == "text") {
		return parse_text((Game_UI::Layout&&)layout, params, template_params);
	} else if (type_name == "image") {
		return parse_image((Game_UI::Layout&&)layout, params, template_params);
	} else if (type_name == "button") {
		return parse_button((Game_UI::Layout&&)layout, params, template_params);
	} else {
		SG_ERROR("Invalid widget type \"%s\"", type_name.data());
		return make_own_ptr<Game_UI::Box>(Game_UI::Layout{});
	}
}

Game_UI::Layout GUI_Loader::parse_layout(const JSON::Object_View& json, const JSON::Object_View& template_params)
{
	// FIXME - what if the numbers don't add up to 1??
	Array<Game_UI::Size> rows;
	Array<Game_UI::Size> columns;

	json["rows"].as_array().for_each([&](const JSON::Value_View& row){
		rows.push_back(JSON_Types::parse_size(row.as_object(), template_params));
	});

	json["columns"].as_array().for_each([&](const JSON::Value_View& column){
		columns.push_back(JSON_Types::parse_size(column.as_object(), template_params));
	});

	return Game_UI::Layout{rows, columns};
}

Game_UI::Widget_Ptr GUI_Loader::parse_box(Game_UI::Layout&& layout, const JSON::Object_View& params, const JSON::Object_View& template_params)
{
	Own_Ptr<Game_UI::Box> widget = make_own_ptr<Game_UI::Box>((Game_UI::Layout&&)layout);

	if (params.has("colour")) {
		widget->colour = JSON_Types::parse_colour(resolve_templated_value(params["colour"], template_params).as_object());
	}

	return widget;
}

Game_UI::Widget_Ptr GUI_Loader::parse_text(Game_UI::Layout&& layout, const JSON::Object_View& params, const JSON::Object_View& template_params)
{
	Resource_Handle<Font> font = m_font_manager.get(resolve_templated_value(params["font"], template_params).as_string(""), false);
	Own_Ptr<Game_UI::Text> widget = make_own_ptr<Game_UI::Text>(font, (Game_UI::Layout&&)layout);

	widget->text = JSON_Types::parse_formatted_text(resolve_templated_value(params["text"], template_params));
	widget->size = resolve_templated_value(params["size"], template_params).as_int(16);
	if (params.has("align")) {
		widget->align = JSON_Types::parse_text_align(resolve_templated_value(params["align"], template_params).as_string("left"));
	}

	return widget;
}

Game_UI::Widget_Ptr GUI_Loader::parse_image(Game_UI::Layout&& layout, const JSON::Object_View& params, const JSON::Object_View& template_params)
{
	Own_Ptr<Game_UI::Image> widget = make_own_ptr<Game_UI::Image>((Game_UI::Layout&&)layout);

	if (params.has("sprite")) {
		widget->sprite = JSON_Types::parse_sprite(
			resolve_templated_value(params["sprite"], template_params).as_object(),
			m_texture_manager
		);
	}

	return widget;
}

Game_UI::Widget_Ptr GUI_Loader::parse_button(Game_UI::Layout&& layout, const JSON::Object_View& params, const JSON::Object_View& template_params)
{
	Game_UI::Widget_Ptr content_normal = parse_widget(resolve_templated_value(params["normal"], template_params).as_object(), template_params);
	Game_UI::Widget_Ptr content_focused = parse_widget(resolve_templated_value(params["focused"], template_params).as_object(), template_params);

	return make_own_ptr<Game_UI::Button>((Game_UI::Widget_Ptr&&)content_normal, (Game_UI::Widget_Ptr&&)content_focused, (Game_UI::Layout&&)layout);
}

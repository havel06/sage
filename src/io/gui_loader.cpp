#include "gui_loader.hpp"
#include "graphics/game_ui/widget_factories/box.hpp"
#include "graphics/game_ui/widget_factories/button.hpp"
#include "graphics/game_ui/widget_factories/image.hpp"
#include "graphics/game_ui/widget_factories/text.hpp"
#include "graphics/game_ui/layout.hpp"
#include "graphics/game_ui/widget.hpp"
#include "graphics/game_ui/widgets/box.hpp"
#include "io/json_types.hpp"
#include "io/resource/texture_manager.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "io/resource/font_manager.hpp"
#include "io/template.hpp"
#include "io/parameter_parser.hpp"

GUI_Loader::GUI_Loader(Font_Manager& font_mgr, Parameter_Parser& parameter_parser, const String& project_root) :
	m_font_manager{font_mgr},
	m_parameter_parser{parameter_parser}
{
	m_project_root = project_root;
}

Game_UI::Widget_Ptr GUI_Loader::load(const String& filename)
{
	return load_factory(filename)->make_widget();
}

Own_Ptr<Game_UI::Widget_Factory> GUI_Loader::load_factory(const String& filename)
{
	String path = m_project_root;
	path.append('/');
	path.append(filename);

	JSON::Object json = JSON::Object::from_file(path.data());
	auto loaded_widget = parse_widget_factory(json.get_view(), JSON::Object{}.get_view());

	if (loaded_widget) {
		SG_INFO("Loaded GUI widget \"%s\"", filename.data());
		return loaded_widget;
	} else {
		SG_ERROR("Couldn't load GUI widget \"%s\", using fallback instead", filename.data());
		return make_own_ptr<Game_UI::Box_Factory>();
	}
}

Own_Ptr<Game_UI::Widget_Factory> GUI_Loader::parse_widget_factory(const JSON::Object_View& json, const JSON::Object_View& template_params)
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
		return parse_templated_widget_factory(template_json.get_view(), params);
	} else {
		return parse_templated_widget_factory(json, template_params);
	}
}

Own_Ptr<Game_UI::Widget_Factory> GUI_Loader::parse_templated_widget_factory(
	const JSON::Object_View& widget_json,
	const JSON::Object_View& template_params
)
{
	String type = widget_json["type"].as_string("");

	if (type.empty()) {
		SG_ERROR("Missing widget type.");
		return nullptr;
	}

	Own_Ptr<Game_UI::Widget_Factory> widget_factory = create_widget_from_type_name(type);
	widget_factory->layout_description = parse_layout(widget_json["layout"].as_object(), template_params);
	widget_factory->position_row = widget_json["row"].as_int(0);
	widget_factory->position_column = widget_json["column"].as_int(0);

	// Parameters
	JSON::Object_View params = widget_json["parameters"].as_object();
	parse_widget_parameters(*widget_factory, params, template_params);

	// Children
	if (widget_json.has("children"))
		widget_factory->children = parse_widget_children(widget_json["children"].as_array(), template_params);

	return widget_factory;
}

Array<Own_Ptr<Game_UI::Widget_Factory>> GUI_Loader::parse_widget_children(
	const JSON::Array_View& children_json,
	const JSON::Object_View& template_params
)
{
	Array<Own_Ptr<Game_UI::Widget_Factory>> children;

	children_json.for_each([&](const JSON::Value_View& value){
		// FIXME - should whole widgets be templatable? how?
		JSON::Object_View child = resolve_templated_value(value, template_params).as_object();
		children.push_back(parse_widget_factory(child, template_params));
	});

	return children;
}

Own_Ptr<Game_UI::Widget_Factory> GUI_Loader::create_widget_from_type_name(const String& type_name)
{
	if (type_name == "box") {
		return make_own_ptr<Game_UI::Box_Factory>();
	} else if (type_name == "text") {
		return make_own_ptr<Game_UI::Text_Factory>(m_font_manager);
	} else if (type_name == "image") {
		return make_own_ptr<Game_UI::Image_Factory>();
	} else if (type_name == "button") {
		return make_own_ptr<Game_UI::Button_Factory>();
	} else {
		SG_ERROR("Invalid widget type \"%s\"", type_name.data());
		return make_own_ptr<Game_UI::Box_Factory>();
	}
}

Game_UI::Layout_Description GUI_Loader::parse_layout(const JSON::Object_View& json, const JSON::Object_View& template_params)
{
	// FIXME - what if the numbers don't add up to 1??
	Game_UI::Layout_Description desc;

	json["rows"].as_array().for_each([&](const JSON::Value_View& row){
		desc.rows.push_back(JSON_Types::parse_size(row.as_object(), template_params));
	});

	json["columns"].as_array().for_each([&](const JSON::Value_View& column){
		desc.columns.push_back(JSON_Types::parse_size(column.as_object(), template_params));
	});

	return desc;
}

void GUI_Loader::parse_widget_parameters(Game_UI::Widget_Factory& factory,
		const JSON::Object_View& parameters,
		const JSON::Object_View& template_parameters
)
{
	factory.for_each_parameter([&](const String& name, Parameter& parameter){
		if (!parameters.has(name.data())) {
			SG_ERROR("Missing event parameter \"%s\"", name.data());
		}

		const JSON::Value_View& unresolved_value = parameters[name.data()];
		m_parameter_parser.parse(parameter, unresolved_value, template_parameters);
	});
}

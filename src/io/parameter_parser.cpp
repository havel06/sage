#include "parameter_parser.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "json_types.hpp"
#include "sequence/condition_parser.hpp"
#include "template.hpp"
#include "gui_loader.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/battle_units_layout_parameter.hpp"
#include "templating/parameters/colour_parameter.hpp"
#include "templating/parameters/condition_array_parameter.hpp"
#include "templating/parameters/string_array_parameter.hpp"
#include "templating/parameters/condition_parameter.hpp"
#include "templating/parameters/direction_parameter.hpp"
#include "templating/parameters/float_parameter.hpp"
#include "templating/parameters/int_parameter.hpp"
#include "templating/parameters/widget_parameter.hpp"
#include "templating/parameters/formatted_text_parameter.hpp"
#include "templating/parameters/position_parameter.hpp"
#include "templating/parameters/sprite_parameter.hpp"
#include "templating/parameters/target_selection_type_parameter.hpp"
#include "templating/parameters/text_align_parameter.hpp"
#include <assert.h>

class Parameter_Parser::Visitor : public Parameter_Visitor {
	const JSON::Value_View& m_param_json;
	const JSON::Object_View& m_template_params;
	Texture_Manager& m_tex_mgr;
	Condition_Parser& m_condition_parser;
	GUI_Loader& m_gui_loader;

public:
	Visitor(
			const JSON::Value_View& param_json,
			Texture_Manager& tex_mgr,
			Condition_Parser& cond_parser,
			GUI_Loader& gui_loader,
			const JSON::Object_View& template_params) :
		m_param_json{param_json},
		m_template_params{template_params},
		m_tex_mgr{tex_mgr},
		m_condition_parser{cond_parser},
		m_gui_loader{gui_loader}
	{
	}

	void visit(Int_Parameter& param) override {
		param.value = m_param_json.as_int(0);
	}

	void visit(Float_Parameter& param) override {
		param.value = m_param_json.as_float(0);
	}

	void visit(String_Parameter& param) override {
		param.value = m_param_json.as_string("");
	}

	void visit(Direction_Parameter& param) override {
		param.value = direction_from_string(m_param_json.as_string("down"), Direction::down);
	}
	
	void visit(String_Array_Parameter& param) override {
		m_param_json.as_array().for_each([&](const JSON::Value_View& value){
			param.value.push_back(value.as_string(""));
		});
	}

	void visit(Sprite_Parameter& param) override {
		param.value = JSON_Types::parse_animated_sprite(m_param_json.as_object(), m_tex_mgr);
	}

	void visit(Target_Selection_Type_Parameter& param) override {
		param.value = target_selection_type_from_str(m_param_json.as_string("enemy"));
	}

	void visit(Condition_Parameter& param) override {
		param.value = m_condition_parser.parse_condition(m_param_json.as_object(), m_template_params);
	}

	void visit(Condition_Array_Parameter& param) override {
		m_param_json.as_array().for_each([&](const JSON::Value_View& value){
			param.value.push_back(
				m_condition_parser.parse_condition(value.as_object(), m_template_params)
			);
		});
	}

	void visit(Battle_Units_Layout_Parameter& param) override {
		param.value = JSON_Types::parse_battle_units_layout(m_param_json.as_object());
	}

	void visit(Formatted_Text_Parameter& param) override {
		param.value = JSON_Types::parse_formatted_text(m_param_json);
	}

	void visit(Position_Parameter& param) override {
		param.value = JSON_Types::parse_position(m_param_json.as_object());
	}

	void visit(Colour_Parameter& param) override {
		param.value = JSON_Types::parse_colour(m_param_json.as_object());
	}

	void visit(Text_Align_Parameter& param) override {
		param.value = JSON_Types::parse_text_align(m_param_json.as_string("left"));
	}

	void visit(Widget_Parameter& param) override {
		// FIXME - implement
		param.value = m_gui_loader.parse_widget_factory(m_param_json.as_object(), JSON::Object_View{nullptr});
	}
};


Parameter_Parser::Parameter_Parser(Condition_Parser& cond_parser, Texture_Manager& texture_manager, GUI_Loader& gui_loader) :
	m_condition_parser{cond_parser},
	m_texture_manager{texture_manager},
	m_gui_loader{gui_loader}
{
}

void Parameter_Parser::parse(Parameter& parameter, const JSON::Value_View& unresolved_value, const JSON::Object_View& template_parameters)
{
	const JSON::Value_View& resolved_value_json = resolve_templated_value(unresolved_value, template_parameters);
	Visitor visitor{resolved_value_json, m_texture_manager, m_condition_parser, m_gui_loader, template_parameters};
	parameter.accept_visitor(visitor);
}

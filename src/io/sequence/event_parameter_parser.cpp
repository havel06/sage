#include "event_parameter_parser.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "../json_types.hpp"
#include "sequence/event_parameter.hpp"
#include "sequence_loader.hpp"
#include <string.h>
#include <assert.h>


Event_Parameter_Parser::Event_Parameter_Parser(Sequence_Loader& sequence_loader, Texture_Manager& texture_manager) :
	m_sequence_loader{sequence_loader},
	m_texture_manager{texture_manager}
{
}

void Event_Parameter_Parser::parse(Event_Parameter& parameter, const JSON::Value_View& unresolved_value, const JSON::Object_View& template_parameters)
{
	const JSON::Value_View& resolved_value_json = resolve_value(unresolved_value, template_parameters);

	// FIXME - refactor visitor away
	class Visitor : public Event_Parameter_Visitor {
		const JSON::Value_View& m_param_json;
		const JSON::Object_View& m_template_params;
		Texture_Manager& m_tex_mgr;
		Sequence_Loader& m_seq_loader;

	public:
		Visitor(
				const JSON::Value_View& param_json,
				Texture_Manager& tex_mgr,
				Sequence_Loader& seq_loader,
				const JSON::Object_View& template_params) :
			m_param_json{param_json},
			m_template_params{template_params},
			m_tex_mgr{tex_mgr},
			m_seq_loader{seq_loader}
		{
		}

		void visit(Int_Event_Parameter& param) override {
			param.value = m_param_json.as_int(0);
		}

		void visit(Float_Event_Parameter& param) override {
			param.value = m_param_json.as_float(0);
		}

		void visit(String_Event_Parameter& param) override {
			param.value = m_param_json.as_string("");
		}

		void visit(Direction_Event_Parameter& param) override {
			param.value = direction_from_string(m_param_json.as_string("down"));
		}
		
		void visit(String_Array_Event_Parameter& param) override {
			m_param_json.as_array().for_each([&](const JSON::Value_View& value){
				param.value.push_back(value.as_string(""));
			});
		}

		void visit(Sprite_Event_Parameter& param) override {
			param.value = JSON_Types::parse_animated_sprite(m_param_json.as_object(), m_tex_mgr);
		}

		void visit(Target_Selection_Type_Event_Parameter& param) override {
			param.value = target_selection_type_from_str(m_param_json.as_string("enemy"));
		}

		void visit(Condition_Event_Parameter& param) override {
			param.value = m_seq_loader.parse_condition(m_param_json.as_object(), m_template_params);
		}
	};

	Visitor visitor{resolved_value_json, m_texture_manager, m_sequence_loader, template_parameters};
	parameter.accept_visitor(visitor);
}

JSON::Value_View Event_Parameter_Parser::resolve_value(const JSON::Value_View& val, const JSON::Object_View& template_parameters)
{
	if (val.is_string()) {
		const char* str_value = val.as_string("");

		if (strlen(str_value) > 1 && str_value[0] == '$') {
			const char* param_name = str_value + 1;
			if (template_parameters.has(param_name)) {
				return template_parameters.get(param_name);
			} else {
				SG_ERROR("Missing sequence template parameter \"%s\"", param_name);
				assert(false);
			}
		}
	}

	return val;
}

#include "sequence_loader.hpp"
#include "character_profile.hpp"
#include "combat/battle_desc.hpp"
#include "graphics/ui/layout.hpp"
#include "io/gui_loader.hpp"
#include "io/resource/texture_manager.hpp"
#include "sequence/event_parameter.hpp"
#include "utils/move.hpp"
#include "sequence/conditions/has_item.hpp"
#include "sequence/conditions/not.hpp"
#include "sequence/event_factories/activate_sequence.hpp"
#include "sequence/event_factories/add_quest.hpp"
#include "sequence/event_factories/finish_quest.hpp"
#include "sequence/event_factories/add_to_party.hpp"
#include "sequence/event_factories/delay.hpp"
#include "sequence/event_factories/change_sprite.hpp"
#include "sequence/event_factories/display_text.hpp"
#include "sequence/event_factories/echo.hpp"
#include "sequence/event_factories/change_map.hpp"
#include "sequence/event_factories/give_item.hpp"
#include "sequence/event_factories/move_entity.hpp"
#include "sequence/event_factories/remove_item.hpp"
#include "sequence/event_factories/rotate_entity.hpp"
#include "sequence/event_factories/play_music.hpp"
#include "sequence/event_factories/play_sound.hpp"
#include "sequence/event_factories/show_gui.hpp"
#include "sequence/event_factories/hide_gui.hpp"
#include "sequence/event_factories/teleport_player.hpp"
#include "sequence/event_factories/teleport_entity.hpp"
#include "sequence/event_factories/enable_player_actions.hpp"
#include "sequence/event_factories/disable_player_actions.hpp"
#include "sequence/event_factories/enter_combat.hpp"
#include "sequence/event_factories/zoom_camera.hpp"
#include "sequence/event_factories/select_target.hpp"
#include "sequence/sequence.hpp"
#include "sequence/event_factory.hpp"
#include "utils/direction.hpp"
#include "utils/file.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "json_types.hpp"
#include "resource/resource_system.hpp"

Sequence_Loader::Sequence_Loader(const String& resource_root_path, Resource_System& res_system, Game_Facade& facade, GUI_Loader& gui_loader) :
	m_facade{facade},
	m_resource_system{res_system},
	m_gui_loader{gui_loader}
{
	m_resource_root_path = resource_root_path;
}

Sequence Sequence_Loader::load(const String& filename)
{
	SG_DEBUG("Parsing sequence %s", filename.data());
	const JSON::Object json = JSON::Object::from_file(filename.data());
	const JSON::Object_View view = json.get_view();

	if (view.has("from_template")) {
		// Load sequence from template
		JSON::Object_View template_spec = view["from_template"].as_object();
		String template_filename = m_resource_root_path;
		template_filename.append('/');
		template_filename.append(template_spec["template"].as_string());
		JSON::Object_View params = template_spec["parameters"].as_object();

		JSON::Object template_json = JSON::Object::from_file(template_filename.data());

		SG_DEBUG("Parsing sequence template %s", template_filename.data());
		return load_templated_sequence(filename, template_json.get_view(), params);

	} else {
		// Load normal, non-templated sequence
		JSON::Object empty_parameters;
		return load_templated_sequence(filename, view, empty_parameters.get_view());
	}
}

Sequence Sequence_Loader::load_templated_sequence(const String& final_filename,
		const JSON::Object_View& template_json,
		const JSON::Object_View& parameters)
{
	Sequence sequence(final_filename);

	if (template_json.has("repeatable")) {
		sequence.repeatable = template_json["repeatable"].as_bool();
	}

	// Events
	template_json["events"].as_array().for_each([&](const JSON::Value_View& event_json) {
		Event_Ptr event = parse_event(event_json.as_object(), parameters);

		if (event)
			sequence.add_event(move(event));
	});

	// Condition
	if (template_json.has("condition")) {
		sequence.set_condition(parse_condition(template_json["condition"].as_object()));
	}

	return sequence;
}

Event_Ptr Sequence_Loader::parse_event(const JSON::Object_View& json,
		const JSON::Object_View& template_params)
{
	const String type = json["type"].as_string();
	const JSON::Object_View params = json["parameters"].as_object();
	Own_Ptr<Event_Factory> factory = get_factory_for_event_type(type);

	if (factory) {
		parse_event_parameters(*factory, params, template_params);

		Event_Ptr loaded_event = factory->make_event(m_facade);

		if (json.has("asynchronous")) {
			loaded_event->asynchronous = json["asynchronous"].as_bool();
		}

		return loaded_event;
	} else {
		return nullptr;
	}
}

Own_Ptr<Event_Factory> Sequence_Loader::get_factory_for_event_type(const String& type)
{
	if (type == "echo") {
		return make_own_ptr<Event_Factories::Echo>();
	} else if (type == "display_text") {
		return make_own_ptr<Event_Factories::Display_Text>();
	} else if (type == "delay") {
		return make_own_ptr<Event_Factories::Delay>();
	} else if (type == "give_item") {
		return make_own_ptr<Event_Factories::Give_Item>();
	} else if (type == "remove_item") {
		return make_own_ptr<Event_Factories::Remove_Item>();
	} else if (type == "change_map") {
		return make_own_ptr<Event_Factories::Change_Map>();
	} else if (type == "teleport_player") {
		return make_own_ptr<Event_Factories::Teleport_Player>();
	} else if (type == "teleport_entity") {
		return make_own_ptr<Event_Factories::Teleport_Entity>();
	} else if (type == "move_entity") {
		return make_own_ptr<Event_Factories::Move_Entity>();
	} else if (type == "rotate_entity") {
		return make_own_ptr<Event_Factories::Rotate_Entity>();
	} else if (type == "play_sound") {
		return make_own_ptr<Event_Factories::Play_Sound>(m_resource_system.sound_manager);
	} else if (type == "play_music") {
		return make_own_ptr<Event_Factories::Play_Music>(m_resource_system.sound_manager);
	} else if (type == "change_sprite") {
		return make_own_ptr<Event_Factories::Change_Sprite>();
	} else if (type == "activate_sequence") {
		return make_own_ptr<Event_Factories::Activate_Sequence>(m_resource_system.sequence_manager);
	} else if (type == "add_to_party") {
		return make_own_ptr<Event_Factories::Add_To_Party>(m_resource_system.character_profile_manager);
	} else if (type == "add_quest") {
		return make_own_ptr<Event_Factories::Add_Quest>();
	} else if (type == "finish_quest") {
		return make_own_ptr<Event_Factories::Finish_Quest>();
	} else if (type == "zoom_camera") {
		return make_own_ptr<Event_Factories::Zoom_Camera>();
	} else if (type == "enable_player_actions") {
		return make_own_ptr<Event_Factories::Enable_Player_Actions>();
	} else if (type == "disable_player_actions") {
		return make_own_ptr<Event_Factories::Disable_Player_Actions>();
	} else if (type == "show_gui") {
		return make_own_ptr<Event_Factories::Show_GUI>(m_gui_loader);
	} else if (type == "hide_gui") {
		return make_own_ptr<Event_Factories::Hide_GUI>();
	} else if (type == "enter_combat") {
		return make_own_ptr<Event_Factories::Enter_Combat>(m_resource_system.sequence_manager, m_resource_system.character_profile_manager);
	} else if (type == "select_target") {
		return make_own_ptr<Event_Factories::Select_Target>();
	} else {
		SG_WARNING("Invalid event type \"%s\"", type.data());
		return nullptr;
	}
}

void Sequence_Loader::parse_event_parameters(Event_Factory& factory,
		const JSON::Object_View& parameters,
		const JSON::Object_View& template_parameters)
{
	// FIXME - refactor

	factory.for_each_parameter([&](const String& name, Event_Parameter& parameter){
		if (!parameters.has(name.data())) {
			SG_ERROR("Missing event parameter \"%s\"", name.data());
			assert(false);
		}

		const JSON::Value_View& parameter_json = resolve_value(parameters[name.data()], template_parameters);

		class Visitor : public Event_Parameter_Visitor {
			const JSON::Value_View& m_param_json;
			Texture_Manager& m_tex_mgr;

		public:
			Visitor(const JSON::Value_View& param_json, Texture_Manager& tex_mgr) :
				m_param_json{param_json},
				m_tex_mgr{tex_mgr}
			{
			}

			void visit(Int_Event_Parameter& param) override {
				param.value = m_param_json.as_int();
			}

			void visit(Float_Event_Parameter& param) override {
				param.value = m_param_json.as_float();
			}

			void visit(String_Event_Parameter& param) override {
				param.value = m_param_json.as_string();
			}

			void visit(Direction_Event_Parameter& param) override {
				param.value = direction_from_string(m_param_json.as_string());
			}
			
			void visit(String_Array_Event_Parameter& param) override {
				m_param_json.as_array().for_each([&](const JSON::Value_View& value){
					param.value.push_back(value.as_string());
				});
			}

			void visit(Sprite_Event_Parameter& param) override {
				param.value = JSON_Types::parse_animated_sprite(m_param_json.as_object(), m_tex_mgr);
			}

			void visit(Target_Selection_Type_Event_Parameter& param) override {
				param.value = target_selection_type_from_str(m_param_json.as_string());
			}
		};

		Visitor visitor{parameter_json, m_resource_system.texture_manager};
		parameter.accept_visitor(visitor);
	});
}

Condition_Ptr Sequence_Loader::parse_condition(const JSON::Object_View& json)
{
	const String type = json["type"].as_string();
	const JSON::Object_View params = json["parameters"].as_object();

	if (type == "has_item") {
		String item = params["item"].as_string();
		const int count = params["count"].as_int();
		return make_own_ptr<Conditions::Has_Item>(m_facade, (String&&)item, count);
	} else if (type == "not") {
		Condition_Ptr sub_condition = parse_condition(params["condition"].as_object());
		return make_own_ptr<Conditions::Not>(m_facade, (Condition_Ptr&&)sub_condition);
	} else {
		SG_WARNING("Invalid event type \"%s\"", type.data());
		return nullptr;
	}
}

JSON::Value_View Sequence_Loader::resolve_value(const JSON::Value_View& val,
		const JSON::Object_View& parameters)
{
	if (val.is_string()) {
		const char* str_value = val.as_string();

		if (strlen(str_value) > 1 && str_value[0] == '$') {
			const char* param_name = str_value + 1;
			if (parameters.has(param_name)) {
				return parameters.get(param_name);
			} else {
				SG_ERROR("Missing sequence template parameter \"%s\"", param_name);
				assert(false);
			}
		}
	}

	return val;
}

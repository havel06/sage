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
#include "sequence/events/dummy.hpp"
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
	template_json["events"].as_array().for_each([&](const JSON::Value_View& event) {
		sequence.add_event(parse_event(event.as_object(), parameters));
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
	// FIXME - either use resolve_value everywhere, or refactor the whole thing

	const String type= json["type"].as_string();
	const JSON::Object_View params = json["parameters"].as_object();
	Event_Ptr loaded_event;

	if (type == "echo") {
		Event_Factories::Echo factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "display_text") {
		Event_Factories::Display_Text factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "delay") {
		Event_Factories::Delay factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "give_item") {
		Event_Factories::Give_Item factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "remove_item") {
		Event_Factories::Remove_Item factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "change_map") {
		Event_Factories::Change_Map factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "teleport_player") {
		Event_Factories::Teleport_Player factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "teleport_entity") {
		Event_Factories::Teleport_Entity factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "move_entity") {
		Event_Factories::Move_Entity factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "rotate_entity") {
		Event_Factories::Rotate_Entity factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "play_sound") {
		Event_Factories::Play_Sound factory(m_resource_system.sound_manager);
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "play_music") {
		Event_Factories::Play_Music factory(m_resource_system.sound_manager);
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "change_sprite") {
		Event_Factories::Change_Sprite factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "activate_sequence") {
		Event_Factories::Activate_Sequence factory(m_resource_system.sequence_manager);
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "add_to_party") {
		Event_Factories::Add_To_Party factory(m_resource_system.character_profile_manager);
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "add_quest") {
		Event_Factories::Add_Quest factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "finish_quest") {
		Event_Factories::Finish_Quest factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "zoom_camera") {
		Event_Factories::Zoom_Camera factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "enable_player_actions") {
		Event_Factories::Enable_Player_Actions factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "disable_player_actions") {
		Event_Factories::Disable_Player_Actions factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "show_gui") {
		Event_Factories::Show_GUI factory(m_gui_loader);
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "hide_gui") {
		Event_Factories::Hide_GUI factory;
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else if (type == "enter_combat") {
		Event_Factories::Enter_Combat factory(m_resource_system.sequence_manager, m_resource_system.character_profile_manager);
		parse_event_parameters(factory, params, template_params);
		loaded_event = factory.make_event(m_facade);
	} else {
		SG_WARNING("Invalid event type \"%s\"", type.data());
		loaded_event = make_own_ptr<Events::Dummy>(m_facade);
	}

	if (json.has("asynchronous")) {
		loaded_event->asynchronous = json["asynchronous"].as_bool();
	}

	return loaded_event;
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

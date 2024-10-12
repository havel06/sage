#include "event_parser.hpp"
#include "io/gui_loader.hpp"
#include "sequence/event.hpp"
#include "utils/json.hpp"
#include "utils/own_ptr.hpp"
#include "utils/log.hpp"
#include "../resource/resource_system.hpp"
#include "event_parameter_parser.hpp"
#include "sequence/event_factory.hpp"
#include "sequence/event_factories/activate_sequence.hpp"
#include "sequence/event_factories/move_camera.hpp"
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
#include "sequence/event_factories/remove_sprite.hpp"
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
#include "sequence/event_factories/change_target_hp.hpp"
#include "sequence/event_factories/change_current_unit_hp.hpp"
#include "sequence/event_factories/change_all_ally_units_hp.hpp"
#include "sequence/event_factories/change_all_enemy_units_hp.hpp"
#include "sequence/event_factories/end_turn.hpp"
#include "sequence/event_factories/teleport_camera_to_player.hpp"

Event_Parser::Event_Parser(Event_Parameter_Parser& param_parser, Resource_System& res_system, GUI_Loader& gui_loader, Game_Facade& game_facade) :
	m_event_parameter_parser{param_parser},
	m_facade{game_facade},
	m_resource_system{res_system},
	m_gui_loader{gui_loader}
{
}

Own_Ptr<Event> Event_Parser::parse_event(const JSON::Object_View& json,
		const JSON::Object_View& template_params)
{
	const String type = json["type"].as_string("");
	if (type.empty()) {
		SG_ERROR("Missing event type.");
		return nullptr;
	}

	const JSON::Object_View params = json["parameters"].as_object();
	Own_Ptr<Event_Factory> factory = get_factory_for_event_type(type);

	if (factory) {
		parse_event_parameters(*factory, params, template_params);

		Own_Ptr<Event> loaded_event = factory->make_event(m_facade);

		if (json.has("asynchronous")) {
			loaded_event->asynchronous = json["asynchronous"].as_bool(false);
		}

		return loaded_event;
	} else {
		return nullptr;
	}
}


Own_Ptr<Event_Factory> Event_Parser::get_factory_for_event_type(const String& type)
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
	} else if (type == "remove_sprite") {
		return make_own_ptr<Event_Factories::Remove_Sprite>();
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
	} else if (type == "change_target_hp") {
		return make_own_ptr<Event_Factories::Change_Target_HP>();
	} else if (type == "change_current_unit_hp") {
		return make_own_ptr<Event_Factories::Change_Current_Unit_HP>();
	} else if (type == "change_all_ally_units_hp") {
		return make_own_ptr<Event_Factories::Change_All_Ally_Units_HP>();
	} else if (type == "change_all_enemy_units_hp") {
		return make_own_ptr<Event_Factories::Change_All_Enemy_Units_HP>();
	} else if (type == "end_turn") {
		return make_own_ptr<Event_Factories::End_Turn>();
	} else if (type == "move_camera") {
		return make_own_ptr<Event_Factories::Move_Camera>();
	} else if (type == "teleport_camera_to_player") {
		return make_own_ptr<Event_Factories::Teleport_Camera_To_Player>();
	} else {
		SG_ERROR("Invalid event type \"%s\"", type.data());
		return nullptr;
	}
}

void Event_Parser::parse_event_parameters(Event_Factory& factory,
		const JSON::Object_View& parameters,
		const JSON::Object_View& template_parameters)
{
	factory.for_each_parameter([&](const String& name, Event_Parameter& parameter){
		if (!parameters.has(name.data())) {
			SG_ERROR("Missing event parameter \"%s\"", name.data());
			assert(false);
		}

		const JSON::Value_View& unresolved_value = parameters[name.data()];
		m_event_parameter_parser.parse(parameter, unresolved_value, template_parameters);
	});
}


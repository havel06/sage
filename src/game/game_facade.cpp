#include "game_facade.hpp"
#include "graphics/scriptable_gui.hpp"
#include "character_profile.hpp"
#include "combat/battle_desc.hpp"
#include "combat/battle_turn.hpp"
#include "game/game_logic.hpp"
#include "io/savegame/saveload_system.hpp"
#include "utils/move.hpp"
#include "io/savegame/map_saveloader.hpp"
#include "io/savegame/sequence_saveloader.hpp"
#include "io/savegame/game_saveloader.hpp"
#include "map/entity.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include "game_logic_state_normal.hpp"
#include "music_player.hpp"
#include "graphics/camera_controller.hpp"
#include "io/resource/map_manager.hpp"
#include "io/resource/sequence_manager.hpp"
#include "combat/combat.hpp"
#include "map/position.hpp"

Game_Facade::Game_Facade(
		Music_Player& music_player,
		Game_Logic_State_Normal& logic,
		Camera_Controller& controller,
		Saveload_System& saveload_system,
		Game_Logic& game_logic,
		Scriptable_GUI& scriptable_gui,
		Party& party,
		bool no_auto_save) :
	m_music_player{music_player},
	m_logic_normal{logic},
	m_camera_controller{controller},
	m_saveloader{saveload_system},
	m_game_logic{game_logic},
	m_scriptable_gui{scriptable_gui},
	m_party{party},
	m_no_auto_save{no_auto_save}
{
}

void Game_Facade::set_layer_opacity(const String& layer_name, float opacity)
{
	Tile_Layer* layer = m_logic_normal.get_map().layers.find_layer(layer_name);

	if (!layer) {
		SG_ERROR("Layer \"%s\" not found.", layer_name.data());
		return;
	}
	
	layer->set_opacity(opacity);
}

float Game_Facade::get_layer_opacity(const String& layer_name) const
{
	Tile_Layer* layer = m_logic_normal.get_map().layers.find_layer(layer_name);

	if (!layer) {
		SG_ERROR("Layer \"%s\" not found.", layer_name.data());
		return 0;
	}

	return layer->get_opacity();
}

Vec2f Game_Facade::resolve_position(const Position& position)
{
	return position.resolve(m_logic_normal.get_map().entities);
}

bool Game_Facade::is_passable(const Position& position)
{
	return m_logic_normal.get_map().is_passable(resolve_position(position));
}

void Game_Facade::set_current_map(const String& filename)
{
	// FIXME - wouldn't time-based periodic saves be better?
	// FIXME - this should probably happen in Game_Logic_Normal
	if (!m_no_auto_save)
		save_game(); // Save everything

	m_logic_normal.set_current_map(filename);
}

void Game_Facade::teleport_player(const Position& position)
{
	m_logic_normal.get_player().position = resolve_position(position).round();
}

void Game_Facade::teleport_entity(const String& entity_name, const Position& position)
{
	Entity* entity = m_logic_normal.get_map().entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return;
	}

	entity->position = resolve_position(position).round();
}

void Game_Facade::display_text(const Game_UI::Formatted_Text& message)
{
	m_logic_normal.text_box.push_message(message);
}

bool Game_Facade::is_text_box_shown() const
{
	return m_logic_normal.text_box.contains_message();	
}

void Game_Facade::give_item(const String& id, int count)
{
	//SG_DEBUG("Give item \"%s\" * %d", id.data(), count);
	m_logic_normal.inventory.add_item(id, count);
}

void Game_Facade::remove_item(const String& id, int count)
{
	m_logic_normal.inventory.remove_item(id, count);
}

void Game_Facade::set_entity_sprite(const String& entity_name, const Animated_Sprite& sprite)
{
	Entity* entity = m_logic_normal.get_map().entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return;
	}

	entity->sprite = sprite;
	entity->sprite.reset_animation();
	SG_DEBUG("Changed sprite of entity \"%s\"", entity_name.data());
}

void Game_Facade::play_music(Resource_Handle<Sound> music)
{
	m_music_player.play(music);
}

int Game_Facade::get_owned_item_count(const String& id)
{
	return m_logic_normal.inventory.get_item_count(id);
}

Vec2i Game_Facade::get_entity_position(const String& entity_name)
{
	Entity* entity = m_logic_normal.get_map().entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return {};
	}

	return entity->position;
}

Direction Game_Facade::get_player_direction()
{
	return get_entity_direction("Player");
}

Direction Game_Facade::get_entity_direction(const String& entity_name)
{
	Entity* entity = m_logic_normal.get_map().entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return {};
	}

	return entity->get_look_direction();
}

void Game_Facade::move_entity(const String& entity_name, const Position& position)
{
	const Vec2i pos_resolved = resolve_position(position).round();
	Entity* entity = m_logic_normal.get_map().entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return;
	}

	if (entity->position == pos_resolved)
		return;

	entity->move(vec2i_to_direction(pos_resolved - entity->position, Direction::down));
}

void Game_Facade::rotate_player(Direction direction)
{
	Entity& entity = m_logic_normal.get_player();
	entity.look(direction);
}

void Game_Facade::rotate_entity(const String& entity_name, Direction direction)
{
	Entity* entity = m_logic_normal.get_map().entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return;
	}

	entity->look(direction);
}

void Game_Facade::set_player_interactions_enabled(bool enabled)
{
	m_logic_normal.player_actions_disabled = !enabled;
}

void Game_Facade::add_to_party(Resource_Handle<Character_Profile> profile)
{
	m_party.add_character(profile);
}

void Game_Facade::enter_combat(const Battle_Description& description)
{
	// Save game before going to combat
	// FIXME - should this happen in game_logic?
	save_game();

	m_game_logic.enter_combat(description);
}

bool Game_Facade::is_in_combat() const
{
	return m_game_logic.get_state() == Game_Logic_State::combat;
}

void Game_Facade::combat_change_target_hp(int amount)
{
	if (!m_game_logic.state_combat.get_combat().is_active()) {
		SG_ERROR("No active battle.");
		return;
	}

	m_game_logic.state_combat.get_combat().get_battle().get_current_turn().change_target_hp(amount);
}

void Game_Facade::combat_change_all_enemy_units_hp(int amount)
{
	if (!m_game_logic.state_combat.get_combat().is_active()) {
		SG_ERROR("No active battle.");
		return;
	}

	m_game_logic.state_combat.get_combat().get_battle().get_current_turn().change_all_enemy_units_hp(amount);
}

void Game_Facade::combat_change_all_ally_units_hp(int amount)
{
	if (!m_game_logic.state_combat.get_combat().is_active()) {
		SG_ERROR("No active battle.");
		return;
	}

	m_game_logic.state_combat.get_combat().get_battle().get_current_turn().change_all_ally_units_hp(amount);
}

void Game_Facade::combat_change_current_unit_hp(int amount)
{
	if (!m_game_logic.state_combat.get_combat().is_active()) {
		SG_ERROR("No active battle.");
		return;
	}
	m_game_logic.state_combat.get_combat().get_battle().get_current_turn().change_current_unit_hp(amount);
}

void Game_Facade::combat_enter_target_selection(Target_Selection_Type type)
{
	if (!m_game_logic.state_combat.get_combat().is_active()) {
		SG_ERROR("No active battle.");
		return;
	}
	m_game_logic.state_combat.get_combat().get_battle().get_current_turn().enter_target_selection(type);
}

void Game_Facade::combat_end_turn()
{
	if (!m_game_logic.state_combat.get_combat().is_active()) {
		SG_ERROR("No active battle.");
		return;
	}
	m_game_logic.state_combat.get_combat().get_battle().get_current_turn().advance_turn();
}

void Game_Facade::combat_set_current_unit_sprite(const Animated_Sprite& sprite)
{
	if (!m_game_logic.state_combat.get_combat().is_active()) {
		SG_ERROR("No active battle.");
		return;
	}
	m_game_logic.state_combat.get_combat().get_battle().get_current_turn().set_current_unit_sprite(sprite);
}

void Game_Facade::combat_reset_current_unit_sprite()
{
	if (!m_game_logic.state_combat.get_combat().is_active()) {
		SG_ERROR("No active battle.");
		return;
	}
	m_game_logic.state_combat.get_combat().get_battle().get_current_turn().reset_current_unit_sprite();
}

Battle_Turn_State Game_Facade::combat_get_battle_turn_state() const
{
	if (!m_game_logic.state_combat.get_combat().is_active()) {
		SG_ERROR("No active battle.");
		return Battle_Turn_State::finished;
	}

	return m_game_logic.state_combat.get_combat().get_battle().get_current_turn().get_state();
}

void Game_Facade::add_quest(const String& id, const String& name, const String& description)
{
	SG_INFO("Added quest \"%s\"", id.data());
	m_logic_normal.quest_log.add_quest(Quest{
		.id = id,
		.name = name,
		.description = description
	});
}

void Game_Facade::finish_quest(const String& name)
{
	m_logic_normal.quest_log.remove_quest(name);
}

void Game_Facade::zoom_camera(int amount)
{
	m_camera_controller.set_zoom(amount);
}

void Game_Facade::save_game()
{
	// FIXME - should this happend in game_logic instead?
	
	// Only save when out of combat
	if (m_game_logic.get_state() != Game_Logic_State::combat) {
		m_saveloader.save_game();
	}
}

void Game_Facade::show_gui(const String& filename)
{
	m_scriptable_gui.show_widget(filename);
}

void Game_Facade::hide_gui()
{
	m_scriptable_gui.hide_widget();
}

void Game_Facade::move_camera(const Position& position)
{
	return m_camera_controller.set_fixed_target(position.resolve(m_logic_normal.get_map().entities));
}

Vec2f Game_Facade::get_camera_position() const
{
	return m_camera_controller.get_camera_position();
}

void Game_Facade::camera_follow_player()
{
	m_camera_controller.follow_player();
}

void Game_Facade::teleport_camera_to_player()
{
	m_camera_controller.follow_player();
	m_camera_controller.teleport_to(m_logic_normal.get_player().position);
}

#include "game_facade.hpp"
#include "character_profile.hpp"
#include "combat/battle_desc.hpp"
#include "game/game_logic.hpp"
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

Game_Facade::Game_Facade(
		Sequence_Manager& seq_mgr,
		Music_Player& music_player,
		Game_Logic_State_Normal& logic,
		Camera_Controller& controller,
		Map_Saveloader& map_saveloader,
		Game_Saveloader& game_saveloader,
		Game_Logic& game_logic) :
	m_sequence_manager{seq_mgr},
	m_music_player{music_player},
	m_logic_normal{logic},
	m_camera_controller{controller},
	m_map_saveloader{map_saveloader},
	m_game_saveloader{game_saveloader},
	m_game_logic{game_logic}
{
}

void Game_Facade::set_current_map(const String& filename)
{
	// FIXME - wouldn't time-based periodic saves be better?
	save_game(); // Save everything, because why not

	m_logic_normal.set_current_map(filename);
}

void Game_Facade::teleport_player(Vec2i position)
{
	m_logic_normal.get_player().position = position;
}

void Game_Facade::teleport_entity(const String& entity_name, Vec2i position)
{
	Entity* entity = m_logic_normal.get_map().entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return;
	}

	entity->position = position;
}

void Game_Facade::display_text(String&& message)
{
	m_logic_normal.text_box.push_message((String&&)message);
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

void Game_Facade::set_entity_sprite(const String& entity_name, const Sprite& sprite)
{
	Entity* entity = m_logic_normal.get_map().entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return;
	}

	entity->sprite = sprite;
}

void Game_Facade::play_music(Sound music)
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

Direction Game_Facade::get_entity_direction(const String& entity_name)
{
	Entity* entity = m_logic_normal.get_map().entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return {};
	}

	return entity->get_look_direction();
}

void Game_Facade::move_entity(const String& entity_name, Vec2i position)
{
	Entity* entity = m_logic_normal.get_map().entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return;
	}

	if (entity->position == position)
		return;

	Direction direction = vec2i_to_direction(position - entity->position);
	entity->move(direction);
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

void Game_Facade::add_to_party(const Character_Profile& profile)
{
	m_logic_normal.party.add_character(profile);
}

void Game_Facade::enter_combat(const Battle_Description& description)
{
	m_game_logic.enter_combat(description);
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
	m_game_saveloader.save();
	m_map_saveloader.save(m_logic_normal.get_map());
	m_sequence_manager.save();
}

#include "game_facade.hpp"
#include "character_profile.hpp"
#include "io/resource_manager.hpp"
#include "io/map_saveloader.hpp"
#include "map/entity.hpp"
#include "utils/direction.hpp"
#include "utils/log.hpp"
#include "game_logic.hpp"
#include "music_player.hpp"
#include "graphics/camera_controller.hpp"

Game_Facade::Game_Facade(
		Resource_Manager& res_mgr,
		Music_Player& music_player,
		Game_Logic& logic,
		Camera_Controller& controller,
		Map_Saveloader& map_saveloader) :
	m_res_manager{res_mgr},
	m_music_player{music_player},
	m_logic{logic},
	m_camera_controller{controller},
	m_map_saveloader{map_saveloader}
{
}

void Game_Facade::set_current_map(const String& filename)
{
	// Save current map first
	m_map_saveloader.save(m_logic.map);

	m_logic.map = m_res_manager.get_map(filename.data());
	spawn_player();
	m_map_saveloader.load(m_logic.map); // Load progress

	if (m_logic.map.assigned_sequence)
		m_logic.map.assigned_sequence->try_activate();

	SG_INFO("Set current map to \"%s\"", filename.data());
}

void Game_Facade::spawn_player()
{
	// TODO - maybe this should happen in game_logic
	Entity player;

	Character_Profile character = m_logic.party.main_character();

	player.name = character.name;
	player.assigned_character = character;

	m_logic.map.entities.add_entity((Entity&&)player);
}

void Game_Facade::teleport_player(Vec2i position)
{
	m_logic.get_player().position = position;
}

void Game_Facade::teleport_entity(const String& entity_name, Vec2i position)
{
	Entity* entity = m_logic.map.entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return;
	}

	entity->position = position;
}

void Game_Facade::display_text(String&& message)
{
	m_logic.text_box.push_message((String&&)message);
}

bool Game_Facade::is_text_box_shown() const
{
	return m_logic.text_box.contains_message();	
}

void Game_Facade::give_item(const String& id, int count)
{
	//SG_DEBUG("Give item \"%s\" * %d", id.data(), count);
	m_logic.inventory.add_item(id, count);
}

void Game_Facade::remove_item(const String& id, int count)
{
	m_logic.inventory.remove_item(id, count);
}

void Game_Facade::set_entity_sprite(const String& entity_name, const Sprite& sprite)
{
	Entity* entity = m_logic.map.entities.get_entity(entity_name);

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
	return m_logic.inventory.get_item_count(id);
}

Vec2i Game_Facade::get_entity_position(const String& entity_name)
{
	Entity* entity = m_logic.map.entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return {};
	}

	return entity->position;
}

void Game_Facade::move_entity(const String& entity_name, Vec2i position)
{
	Entity* entity = m_logic.map.entities.get_entity(entity_name);

	if (!entity) {
		SG_ERROR("Entity \"%s\" not found", entity_name.data());
		return;
	}

	if (entity->position == position)
		return;

	Direction direction = vec2i_to_direction(position - entity->position);
	entity->move(direction);
}

void Game_Facade::set_player_interactions_enabled(bool enabled)
{
	m_logic.player_actions_disabled = !enabled;
}

void Game_Facade::add_to_party(const Character_Profile& profile)
{
	m_logic.party.add_character(profile);
}

void Game_Facade::enter_combat(const Array<Character_Profile>& enemies, Sequence& win_sequence)
{
	m_logic.combat.start_battle(enemies, win_sequence);
	m_logic.in_combat = true;
}

void Game_Facade::add_quest(const String& id, const String& name, const String& description)
{
	SG_INFO("Added quest \"%s\"", id.data());
	m_logic.quest_log.add_quest(Quest{
		.id = id,
		.name = name,
		.description = description
	});
}

void Game_Facade::finish_quest(const String& name)
{
	m_logic.quest_log.remove_quest(name);
}

void Game_Facade::zoom_camera(int amount)
{
	m_camera_controller.set_zoom(amount);
}

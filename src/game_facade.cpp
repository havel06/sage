#include "game_facade.hpp"
#include "io/resource_manager.hpp"
#include "utils/log.hpp"
#include "game_logic.hpp"
#include "music_player.hpp"

Game_Facade::Game_Facade(Resource_Manager& res_mgr, Music_Player& music_player, Game_Logic& logic) :
	m_res_manager{res_mgr},
	m_music_player{music_player},
	m_logic{logic}
{
}

void Game_Facade::set_current_map(const String& filename)
{
	m_logic.map = m_res_manager.get_map(filename.data());
	spawn_player();
	SG_INFO("Set current map to \"%s\"", filename.data());
}

void Game_Facade::spawn_player()
{
	// TODO - maybe this should happen in game_logic
	Entity player;

	// FIXME - get from config
	player.name = "Player";
	player.sprite = Sprite{m_res_manager.get_texture("textures/sprites.png")};
	player.sprite.texture_clip.size = {16, 16};
	m_logic.map.add_entity((Entity&&)player);
}

void Game_Facade::teleport_player(Vec2i position)
{
	m_logic.get_player().position = position;
}

void Game_Facade::teleport_entity(const String& entity_name, Vec2i position)
{
	Entity* entity = m_logic.map.get_entity(entity_name);

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
	Entity* entity = m_logic.map.get_entity(entity_name);

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

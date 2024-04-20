#pragma once

#include "utils/string.hpp"
#include "utils/vec2.hpp"
#include <raylib/raylib.h>

class Resource_Manager;
class Game_Logic;
class Music_Player;
class Sprite;

// Facade for sequence events to interface with the rest of the game.
class Game_Facade
{
public:
	Game_Facade(Resource_Manager&, Music_Player&, Game_Logic&);
	void set_current_map(const String& filename);
	void teleport_player(Vec2i position);
	void teleport_entity(const String& entity_name, Vec2i position);
	Vec2i get_entity_position(const String& entity_name);
	void move_entity(const String& entity_name, Vec2i position);
	void display_text(String&& message);
	bool is_text_box_shown() const;
	void give_item(const String& id, int count);
	void remove_item(const String& id, int count);
	int get_owned_item_count(const String& id);
	void set_entity_sprite(const String& entity_name, const Sprite& sprite);
	void play_music(Sound);
private:
	void spawn_player();

	Resource_Manager& m_res_manager;
	Music_Player& m_music_player;
	Game_Logic& m_logic;
};

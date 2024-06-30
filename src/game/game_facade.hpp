#pragma once

#include "character_profile.hpp"
#include "combat/battle_desc.hpp"
#include "utils/direction.hpp"
#include "utils/string.hpp"
#include "utils/vec2.hpp"
#include <raylib/raylib.h>
#include "utils/array.hpp"

class Map_Manager;
class Sequence_Manager;
class Game_Logic_State_Normal;
class Music_Player;
class Sprite;
class Sequence;
class Camera_Controller;
class Map_Saveloader;
class Sequence_Saveloader;
class Game_Saveloader;
class Game_Logic;


// FIXME - maybe too many responsibilities

// Facade for sequence events to interface with the rest of the game.
class Game_Facade
{
public:
	// FIXME - maybe too many arguments
	Game_Facade(Sequence_Manager&, Music_Player&, Game_Logic_State_Normal&, Camera_Controller&, Map_Saveloader&, Game_Saveloader&, Game_Logic&);
	void set_current_map(const String& filename);
	const String& get_current_map_path(); // FIXME - should this be here?
	void teleport_player(Vec2i position);
	void set_player_interactions_enabled(bool enabled);
	void teleport_entity(const String& entity_name, Vec2i position);
	Vec2i get_entity_position(const String& entity_name);
	Direction get_entity_direction(const String& entity_name);
	void move_entity(const String& entity_name, Vec2i position);
	void rotate_entity(const String& entity_name, Direction);
	void display_text(String&& message);
	bool is_text_box_shown() const;
	void give_item(const String& id, int count);
	void remove_item(const String& id, int count);
	int get_owned_item_count(const String& id);
	void set_entity_sprite(const String& entity_name, const Sprite& sprite);
	void play_music(Sound);
	void add_to_party(const Character_Profile&);
	void enter_combat(const Battle_Description&);
	void add_quest(const String& id, const String& name, const String& description);
	void finish_quest(const String& id);
	void zoom_camera(int amount);
	void save_game();
private:

	Sequence_Manager& m_sequence_manager;
	Music_Player& m_music_player;
	Game_Logic_State_Normal& m_logic_normal;
	Camera_Controller& m_camera_controller;
	Map_Saveloader& m_map_saveloader;
	Game_Saveloader& m_game_saveloader;
	Game_Logic& m_game_logic;
};

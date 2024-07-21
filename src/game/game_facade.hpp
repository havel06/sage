#pragma once

#include "character_profile.hpp"
#include "combat/battle_desc.hpp"
#include "combat/combat.hpp"
#include "utils/direction.hpp"
#include "utils/string.hpp"
#include "utils/vec2.hpp"
#include "utils/array.hpp"
#include "graphics/ui/widget.hpp"
#include "io/resource/resource_handle.hpp"
#include <raylib/raylib.h>

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
class Scriptable_GUI;
class Combat;


// FIXME - maybe too many responsibilities

// Facade for sequence events to interface with the rest of the game.
class Game_Facade
{
public:
	// FIXME - maybe too many arguments
	Game_Facade(Sequence_Manager&, Music_Player&, Game_Logic_State_Normal&, Camera_Controller&, Map_Saveloader&, Game_Saveloader&, Game_Logic&, Scriptable_GUI&, Combat& combat, Party& party);
	void set_current_map(const String& filename);
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
	void set_entity_sprite(const String& entity_name, const Animated_Sprite& sprite);
	void play_music(Sound);
	void add_to_party(Resource_Handle<Character_Profile>);
	void enter_combat(const Battle_Description&);
	void combat_change_target_hp(int amount);
	void combat_enter_target_selection();
	Combat_State get_combat_state() const;
	void add_quest(const String& id, const String& name, const String& description);
	void finish_quest(const String& id);
	void zoom_camera(int amount);
	void save_game();
	void show_gui(UI::Widget_Ptr&& widget);
	void hide_gui();
private:

	Sequence_Manager& m_sequence_manager;
	Music_Player& m_music_player;
	Game_Logic_State_Normal& m_logic_normal;
	Camera_Controller& m_camera_controller;
	Map_Saveloader& m_map_saveloader;
	Game_Saveloader& m_game_saveloader;
	Game_Logic& m_game_logic;
	Scriptable_GUI& m_scriptable_gui;
	Combat& m_combat;
	Party& m_party;
};

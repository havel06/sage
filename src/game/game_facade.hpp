#pragma once

// FIXME - reduce includes
#include "character_profile.hpp"
#include "combat/battle_desc.hpp"
#include "combat/combat.hpp"
#include "combat/target_selection_type.hpp"
#include "graphics/game_ui/formatted_text.hpp"
#include "utils/direction.hpp"
#include "utils/string.hpp"
#include "utils/vec2.hpp"
#include "utils/array.hpp"
#include "graphics/game_ui/widget.hpp"
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
class Saveload_System;
class Combat;
struct Position;
enum class Battle_Turn_State;

// FIXME - maybe too many responsibilities??

// Facade for sequence events to interface with the rest of the game.
class Game_Facade
{
public:
	// FIXME - maybe too many arguments
	Game_Facade(Music_Player&, Game_Logic_State_Normal&, Camera_Controller&, Saveload_System&, Game_Logic&, Scriptable_GUI&, Party& party, bool no_auto_save);
	Vec2f resolve_position(const Position&);
	bool is_passable(const Position& position);
	void set_current_map(const String& filename);
	void teleport_player(const Position& position);
	void set_player_interactions_enabled(bool enabled);
	void teleport_entity(const String& entity_name, const Position& position);
	Vec2i get_entity_position(const String& entity_name);
	Direction get_entity_direction(const String& entity_name);
	Direction get_player_direction();
	void move_entity(const String& entity_name, const Position& position);
	void rotate_entity(const String& entity_name, Direction);
	void rotate_player(Direction);
	void display_text(const Game_UI::Formatted_Text& message);
	bool is_text_box_shown() const;
	void give_item(const String& id, int count);
	void remove_item(const String& id, int count);
	int get_owned_item_count(const String& id);
	void set_entity_sprite(const String& entity_name, const Animated_Sprite& sprite);
	void play_music(Resource_Handle<Sound>);
	void add_to_party(Resource_Handle<Character_Profile>);
	void set_layer_opacity(const String& layer_name, float opacity);
	float get_layer_opacity(const String& layer_name) const;
	void enter_combat(const Battle_Description&);
	bool is_in_combat() const;
	void combat_change_target_hp(int amount);
	void combat_change_all_enemy_units_hp(int amount);
	void combat_change_all_ally_units_hp(int amount);
	void combat_change_current_unit_hp(int amount);
	void combat_enter_target_selection(Target_Selection_Type);
	void combat_end_turn();
	void combat_set_current_unit_sprite(const Animated_Sprite& sprite);
	void combat_reset_current_unit_sprite();
	Battle_Turn_State combat_get_battle_turn_state() const;
	void add_quest(const String& id, const String& name, const String& description);
	void finish_quest(const String& id);
	void zoom_camera(int amount);
	void save_game();
	void show_gui(const String& filename);
	void hide_gui();
	void move_camera(const Position& position);
	void camera_follow_player();
	void teleport_camera_to_player();
	Vec2f get_camera_position() const;
private:
	Music_Player& m_music_player;
	Game_Logic_State_Normal& m_logic_normal;
	Camera_Controller& m_camera_controller;
	Saveload_System& m_saveloader;
	Game_Logic& m_game_logic;
	Scriptable_GUI& m_scriptable_gui;
	Party& m_party;

	bool m_no_auto_save = false; // Disable auto saving
};

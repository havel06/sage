#pragma once

#include "quest/quest_log.hpp"
#include "utils/string.hpp"

class Game_Logic;
class Texture_Manager;
class Game_Logic_State_Normal;
class Game_Logic_State_Combat;
class Camera_Controller;
class Inventory;
class Party;
class Battle;
class Sequence_Manager;
class User_Directory_Provider;
class Character_Profile_Manager;
class Scriptable_GUI;
class Combat;
namespace JSON {
	class Array_View;
	class Object_View;
	class Array;
	class Object;
}

// FIXME - refactor this mess
class Game_Saveloader
{
public:
	Game_Saveloader(User_Directory_Provider&, const String& project_dir, Camera_Controller&, Sequence_Manager&, Character_Profile_Manager&, Scriptable_GUI& scriptable_gui, Game_Logic& logic);

	void save();
	void load();
	bool can_load(); // Whether a savefile even exists
	void new_game();
private:
	JSON::Array serialise_active_sequences();
	JSON::Array serialise_party();

	void load_active_sequences(const JSON::Array_View&);
	void load_party(const JSON::Array_View&);
	String get_savefile_path();

	Game_Logic& m_logic;
	Camera_Controller& m_camera_controller;
	Sequence_Manager& m_seq_manager;
	User_Directory_Provider& m_user_dir_provider;
	Character_Profile_Manager& m_character_manager;
	Scriptable_GUI& m_scriptable_gui;

	String m_project_dir;
};

#pragma once

#include "quest/quest_log.hpp"
#include "utils/string.hpp"

class Game_Logic_State_Normal;
class Game_Camera;
class Inventory;
class Party;
class Sequence_Manager;
class Savegame_Directory_Provider;
class Character_Profile_Manager;
namespace JSON {
	class Array_View;
	class Array;
}

// FIXME - refactor this mess
class Game_Saveloader
{
public:
	Game_Saveloader(Savegame_Directory_Provider&, const String& project_dir, Game_Logic_State_Normal& logic, Game_Camera&, Inventory& inventory, Quest_Log& quest_log, Sequence_Manager&, Character_Profile_Manager&, Party& party);

	void save();
	void load();
	void new_game();
private:
	JSON::Array serialise_active_sequences();
	JSON::Array serialise_party();
	void load_active_sequences(const JSON::Array_View&);
	void load_party(const JSON::Array_View&);
	String get_savefile_path();

	Game_Logic_State_Normal& m_logic;
	Game_Camera& m_camera;
	Inventory& m_inventory;
	Quest_Log& m_quest_log;
	Sequence_Manager& m_seq_manager;
	Savegame_Directory_Provider& m_savegame_dir_provider;
	Character_Profile_Manager& m_character_manager;
	Party& m_party;

	String m_project_dir;
};

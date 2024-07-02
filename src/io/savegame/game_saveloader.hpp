#pragma once

#include "quest/quest_log.hpp"
#include "utils/string.hpp"

class Game_Facade;
class Game_Camera;
class Inventory;
class Sequence_Manager;
class Savegame_Directory_Provider;
namespace JSON {
	class Array_View;
	class Array;
}

// FIXME - refactor this mess
class Game_Saveloader
{
public:
	Game_Saveloader(Savegame_Directory_Provider&, const String& project_dir, Game_Facade& facade, Game_Camera&, Inventory& inventory, Quest_Log& quest_log, Sequence_Manager&);

	void save();
	void load();
	void new_game();
private:
	JSON::Array serialise_active_sequences();
	void load_active_sequences(const JSON::Array_View&);
	String get_savefile_path();

	Game_Facade& m_game_facade;
	Game_Camera& m_camera;
	Inventory& m_inventory;
	Quest_Log& m_quest_log;
	Sequence_Manager& m_seq_manager;
	Savegame_Directory_Provider& m_savegame_dir_provider;

	String m_project_dir;
};

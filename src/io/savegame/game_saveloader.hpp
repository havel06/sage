#pragma once

#include "quest/quest_log.hpp"
#include "utils/string.hpp"

class Game_Facade;
class Game_Camera;
class Inventory;
class Sequence_Manager;
struct cJSON;

// FIXME - refactor this mess
class Game_Saveloader
{
public:
	Game_Saveloader(const String& project_dir, Game_Facade& facade, Game_Camera&, Inventory& inventory, Quest_Log& quest_log, Sequence_Manager&);

	void set_save_directory(const String& path);

	void save();
	void load();
private:
	cJSON* serialise_active_sequences();
	void load_active_sequences(const cJSON*);

	Game_Facade& m_game_facade;
	Game_Camera& m_camera;
	Inventory& m_inventory;
	Quest_Log& m_quest_log;
	Sequence_Manager& m_seq_manager;

	String m_project_dir;
	String m_savefile_path;
};

#pragma once

#include "utils/string.hpp"

class Game_Facade;

class Game_Saveloader
{
public:
	Game_Saveloader(const String& project_dir, Game_Facade& facade);

	void set_save_directory(const String& path);

	void save();
	void load();
private:

	Game_Facade& m_game_facade;

	String m_project_dir;
	String m_savefile_path;
};

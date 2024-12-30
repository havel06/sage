#pragma once

#include "io/savegame/game_saveloader.hpp"
#include "io/savegame/map_saveloader.hpp"
#include "io/savegame/sequence_saveloader.hpp"

// fwd
class Resource_System;
class Game_Logic;
class Camera_Controller;
class User_Directory_Provider;
class Scriptable_GUI;

class Saveload_System
{
public:
	Saveload_System(
		User_Directory_Provider&,
		Resource_System&,
		Game_Logic&,
		Camera_Controller&,
		Scriptable_GUI&,
		const String& project_dir
	);

	bool can_load();
	void save_game();
	void load_game();
	void load_map(Map& map, const String& filename);
	void new_game();
private:
	Game_Logic_State_Normal& m_logic_normal;

	Game_Saveloader m_game_saveloader;
	Map_Saveloader m_map_saveloader;
	Sequence_Saveloader m_sequence_saveloader;
};

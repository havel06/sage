#pragma once
#include "utils/string.hpp"

// fwd
class Battle;
class Combat;
class Game_Logic;
class Sequence_Manager;
class Character_Profile_Manager;
class Texture_Manager;
namespace JSON {
	class Object;
	class Object_View;
};

class Combat_Saveloader
{
public:
	Combat_Saveloader(Combat&, Sequence_Manager&, Character_Profile_Manager&, Texture_Manager&, Game_Logic&, const String& project_dir);

	JSON::Object save();
	void load(const JSON::Object_View&);
private:
	Combat& m_combat;
	Sequence_Manager& m_seq_manager;
	Character_Profile_Manager& m_character_manager;
	Texture_Manager& m_texture_manager;
	Game_Logic& m_logic;
	String m_project_dir;
};

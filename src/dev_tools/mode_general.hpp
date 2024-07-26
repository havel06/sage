#pragma once

#include "utils/string.hpp"

class Map;
class Game_Facade;
class Game_Logic;

class Dev_Tools_Mode_General
{
public:
	Dev_Tools_Mode_General(Game_Facade&, Game_Logic&, const String& project_root);
	void draw(const Map&);
private:
	String m_project_root;
	Game_Facade& m_game_facade;
	Game_Logic& m_game_logic;
};

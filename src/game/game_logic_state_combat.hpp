#pragma once

// fwd
class Combat;
class Game_Logic;
struct Battle_Description;

class Game_Logic_State_Combat
{
public:
	Game_Logic_State_Combat(Game_Logic&, Combat&);

	void update(float time_delta);
	void start_battle(const Battle_Description&);
private:
	Game_Logic& m_logic;
	Combat& m_combat;
};

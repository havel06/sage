#pragma once

#include "combat/combat.hpp"
#include "utils/passkey.hpp"

// fwd
class Combat;
class Game_Logic;
class Sequence_Manager;
class Party;
struct Battle_Description;

class Game_Logic_State_Combat
{
public:
	Game_Logic_State_Combat(Game_Logic&, Sequence_Manager&, const Party&);

	Combat& get_combat() { return m_combat; }
	void update(Passkey<Game_Logic>, float time_delta);
	void start_battle(Passkey<Game_Logic>, const Battle_Description&);
private:
	Game_Logic& m_logic;
	Sequence_Manager& m_sequence_manager;
	Combat m_combat;
};

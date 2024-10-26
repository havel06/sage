#pragma once

class Battle_Turn;
class Combat_Unit;
struct Combat_Stances;

class Combat_AI
{
public:
	Combat_AI(const Battle_Turn&);

	int decide_ability();
	int decide_enemy_target();
	int decide_ally_target();
private:
	Combat_Stances calculate_stances();

	float calculate_defense_for_unit(const Combat_Unit&);
	float calculate_aid_stance();

	const Battle_Turn& m_battle;
};

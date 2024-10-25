#pragma once

class Battle;
class Combat_Unit;
struct Combat_Stances;

class Combat_AI
{
public:
	Combat_AI(const Battle&);

	int decide_ability();
	int decide_target(bool ally);
private:
	Combat_Stances calculate_stances();

	float calculate_defense_for_unit(const Combat_Unit&);
	float calculate_aid_stance();

	const Battle& m_battle;
};

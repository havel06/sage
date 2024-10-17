#pragma once

class Combat;
class Combat_Unit;
struct Combat_Stances;

class Combat_AI
{
public:
	Combat_AI(const Combat&);

	int decide_ability();
	int decide_target(bool ally);
private:
	Combat_Stances calculate_stances();

	float calcualte_defense_for_unit(const Combat_Unit&);
	float calculate_aid_stance();
	float calculate_offense_stance();

	const Combat& m_combat;
};

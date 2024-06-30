#pragma once

class Combat;
class Combat_Unit;

struct Combat_AI_Decision
{
	int ability_index;
	int target_index;
};

class Combat_AI
{
public:
	Combat_AI(const Combat&);
	Combat_AI_Decision make_decision();
private:
	float evaluate_option(int ability_index, int target_index);
	float evaluate_hero_unit(const Combat_Unit&);

	const Combat& m_combat;
};
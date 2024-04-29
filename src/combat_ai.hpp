#pragma once

class Combat;
class Party;

struct Combat_AI_Decision
{
	int ability_index;
	int target_index;
};

class Combat_AI
{
public:
	Combat_AI(const Combat&, const Party&);
	Combat_AI_Decision make_decision();
private:
	float evaluate_option(int ability_index, int target_index);

	const Combat& m_combat;
	const Party& m_party;
};

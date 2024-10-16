#include "combat_ai.hpp"
#include "ability.hpp"
#include "character_profile.hpp"
#include "combat.hpp"
#include "combat/stances.hpp"
#include "utils/log.hpp"
#include <stdlib.h>
#include <float.h>

Combat_AI::Combat_AI(const Combat& combat) :
	m_combat{combat}
{
}

int Combat_AI::decide_ability()
{
	const Combat_Unit& unit = m_combat.get_unit_on_turn();
	const Combat_Stances current_stances = calculate_stances();

	int best_ability = 0;
	float best_option_score = FLT_MAX;

	// Find best option
	for (int i = 0; i < unit.character.get().abilities.size(); i++) {
		const Ability& ability = unit.character.get().abilities[i];
		const float score = ability.stances.get_dissimilarity_index(current_stances);
		SG_DEBUG("Combat AI: Score for ability \"%s\": %f", ability.name.data(), score);

		if (score < best_option_score) {
			best_ability = i;
			best_option_score = score;
		}
	}

	return best_ability;
}

int Combat_AI::decide_target(bool ally)
{
	const int target_count = ally ? m_combat.get_enemy_count() : m_combat.get_hero_count();
	return rand() % target_count;
}

Combat_Stances Combat_AI::calculate_stances()
{
	const Combat_Unit& unit = m_combat.get_unit_on_turn();

	// Full hp -> defense = 0
	// No hp   -> defense = 1
	const float defense = calcualte_defense_for_unit(unit);
	const float aid = calculate_aid_stance();
	const float offense = 1 - defense;
	
	return Combat_Stances {
		.offense = offense,
		.defense = defense,
		.aid = aid
	};
}

float Combat_AI::calcualte_defense_for_unit(const Combat_Unit& unit)
{
	const float max_hp = unit.character.get().max_hp;
	return (max_hp - unit.get_hp()) / max_hp;
}

float Combat_AI::calculate_aid_stance()
{
	// Calculated as the average defense stance for allies not on turn

	if (m_combat.get_enemy_count() == 1)
		return 0;

	float sum = 0;

	for (int i = 0; i < m_combat.get_enemy_count(); i++) {
		const Combat_Unit& unit = m_combat.get_enemy(i);

		if (unit == m_combat.get_unit_on_turn())
			continue;

		sum += calcualte_defense_for_unit(unit);
	}

	return sum / (m_combat.get_enemy_count() - 1);
}

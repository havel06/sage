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

		for (const Combat_Stances& ability_stances : ability.stances) {
			const float score = ability_stances.get_dissimilarity_index(current_stances);
			SG_DEBUG("Combat AI: Score for ability \"%s\": %f", ability.name.data(), score);

			if (score < best_option_score) {
				best_ability = i;
				best_option_score = score;
			}
		}
	}

	SG_DEBUG("Combat AI: Chose ability %d", best_ability);

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

	//SG_DEBUG("def: %f", calculate_defense_for_unit(unit));
	//SG_DEBUG("of: %f", calculate_offense_stance());
	
	float def = calculate_defense_for_unit(unit);
	
	return Combat_Stances {
		.offense = 1 - def,
		.defense = def,
		.aid = calculate_aid_stance()
	};
}

float Combat_AI::calculate_defense_for_unit(const Combat_Unit& unit)
{
	// Full hp -> defense = 0
	// No hp   -> defense = 1
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

		sum += calculate_defense_for_unit(unit);
	}

	return sum / (m_combat.get_enemy_count() - 1);
}

//float Combat_AI::calculate_offense_stance()
//{
//	// Hero full hp -> offense = 0
//	// Hero no hp   -> offense = 1
//
//	float hero_max_hp_sum = 0;
//	float hero_current_hp_sum = 0;
//
//	for (int i = 0; i < m_combat.get_hero_count(); i++) {
//		hero_max_hp_sum += m_combat.get_hero(i).character.get().max_hp;
//		hero_current_hp_sum += m_combat.get_hero(i).get_hp();
//	}
//
//	return 1 - (hero_current_hp_sum / hero_max_hp_sum);
//}

#include "combat_ai.hpp"
#include "ability.hpp"
#include "character_profile.hpp"
#include "combat.hpp"
#include "utils/log.hpp"
#include <float.h>

Combat_AI::Combat_AI(const Combat& combat) :
	m_combat{combat}
{
}

Combat_AI_Decision Combat_AI::make_decision()
{
	const Combat_Unit& unit = m_combat.get_unit_on_turn();

	int best_ability = 0;
	int best_target = 0;
	float best_option_score = -FLT_MAX;

	// Find best option
	for (int ability = 0; ability < unit.character.abilities.size(); ability++) {
		for (int target = 0; target < m_combat.get_hero_count(); target++) {
			float score = evaluate_option(ability, target);
			if (score > best_option_score) {
				best_ability = ability;
				best_target = target;
				best_option_score = score;
			}
		}
	}

	return Combat_AI_Decision {
		.ability_index = best_ability,
		.target_index = best_target
	};
}

float Combat_AI::evaluate_option(int ability_index, int target_index)
{
	const Ability& ability = m_combat.get_unit_on_turn().character.abilities[ability_index];
	float score = 0;

	for (int i = 0; i < m_combat.get_hero_count(); i++) {
		Combat_Unit hero_unit = m_combat.get_hero(i);

		if (i == target_index) {
			hero_unit.hp -= ability.damage;
		}

		score += evaluate_hero_unit(hero_unit);
	}

	return score;
}

float Combat_AI::evaluate_hero_unit(const Combat_Unit& hero)
{
	// Eliminated - positive score
	if (hero.hp <= 0)
		return 1;

	// Bigger HP portion left is worse
	return -(float)hero.hp / hero.character.max_hp;
}
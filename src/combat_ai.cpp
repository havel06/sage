#include "combat_ai.hpp"
#include "character_profile.hpp"
#include "combat.hpp"
#include "party.hpp"

Combat_AI::Combat_AI(const Combat& combat, const Party& party) :
	m_combat{combat},
	m_party{party}
{
}

Combat_AI_Decision Combat_AI::make_decision()
{
	const Combat_Unit& unit = m_combat.get_unit_on_turn();

	int best_ability = 0;
	int best_target = 0;
	float best_option_score = 0;

	// Find best option
	for (int ability = 0; ability < unit.character.abilities.size(); ability++) {
		for (int target = 0; target < m_party.get_character_count(); target++) {
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
	// FIXME
	(void)ability_index;
	(void)target_index;
	return 0;
}

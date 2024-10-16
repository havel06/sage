#pragma once

struct Combat_Stances
{
	float offense = 0; // Character would like to attack
	float defense = 0; // Character would like to defend
	float aid = 0; // Character would like to aid an ally

	// FIXME - an API that does not break when we add a new stance
	// (maybe use a wrapper for a mathematical vector)
	Combat_Stances normalised() const;

	// The higher the number, the less similar the stances are.
	float get_dissimilarity_index(const Combat_Stances& other) const;
};

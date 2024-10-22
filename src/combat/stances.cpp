#include "stances.hpp"
#include <math.h>
#include <assert.h>

Combat_Stances Combat_Stances::normalised() const
{
	// Avoid division by zero
	if (offense == 0 && defense == 0 && aid == 0) {
		return *this;
	}

	// Normalise it like a vector
	float len = sqrt(offense * offense + defense * defense + aid * aid);
	assert(len != 0);
	float ratio = 1.0 / len;

	return Combat_Stances {
		.offense = offense * ratio,
		.defense = defense * ratio,
		.aid     = aid     * ratio,
	};
}

float Combat_Stances::get_dissimilarity_index(const Combat_Stances& other) const
{
	// This is calculated as euclidian distance between two points.
	// FIXME - make it so that this works when we change the stances

	const Combat_Stances this_normal = normalised();
	const Combat_Stances other_normal = other.normalised();

	return sqrt(
		pow(other_normal.offense - this_normal.offense, 2) +
		pow(other_normal.defense - this_normal.defense, 2) +
		pow(other_normal.aid     - this_normal.aid,     2)
	);
}

#pragma once

#include "utils/array.hpp"
#include "character_profile.hpp"

// fwd
class Sequence;

struct Battle_Description
{
	Array<Character_Profile> enemies;
	Sequence& win_sequence;
	Sequence& lose_sequence;
};

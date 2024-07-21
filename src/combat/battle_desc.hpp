#pragma once

#include "utils/array.hpp"
#include "character_profile.hpp"

// fwd
class Sequence;

struct Battle_Description
{
	Array<Resource_Handle<Character_Profile>> enemies;
	Resource_Handle<Sequence> win_sequence;
	Resource_Handle<Sequence> lose_sequence;
};

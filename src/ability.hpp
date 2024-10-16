#pragma once

#include "utils/string.hpp"
#include "io/resource/resource_handle.hpp"
#include "sequence/sequence.hpp"
#include "combat/stances.hpp"

struct Ability
{
	String name;
	Resource_Handle<Sequence> sequence;
	Combat_Stances stances;
};

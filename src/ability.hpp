#pragma once

#include "utils/string.hpp"

class Sequence;

struct Ability
{
	String name;
	Sequence& sequence;
};

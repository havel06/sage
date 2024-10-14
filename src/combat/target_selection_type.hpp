#pragma once

#include "utils/string.hpp"
#include <assert.h>

enum class Target_Selection_Type
{
	enemy, // Select any enemy
	ally,  // Select any ally
};

inline Target_Selection_Type target_selection_type_from_str(const String& str)
{
	if (str == "enemy")
		return Target_Selection_Type::enemy;
	if (str == "ally")
		return Target_Selection_Type::ally;

	assert(false);
}

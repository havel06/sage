#pragma once

#include "utils/string.hpp"
#include <assert.h>

enum class Target_Selection_Type
{
	enemy, // Select any enemy
	ally,  // Select any ally
	self,  // Automatically selects the character casting the ability FIXME - consider removing
};

inline Target_Selection_Type target_selection_type_from_str(const String& str)
{
	if (str == "enemy")
		return Target_Selection_Type::enemy;
	if (str == "ally")
		return Target_Selection_Type::ally;
	if (str == "self")
		return Target_Selection_Type::self;

	assert(false);
}

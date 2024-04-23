#pragma once

#include "character_profile.hpp"
#include "utils/array.hpp"

class Party
{
public:
	int get_character_count() const;
	Character_Profile& get_main_character();
	Character_Profile& get_character(int index);
private:
	// NOTE - main character is at index 0
	Array<Character_Profile> m_characters;
};

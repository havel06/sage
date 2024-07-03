#pragma once

#include "character_profile.hpp"
#include "utils/array.hpp"

class Party
{
public:
	Party();
	Character_Profile& main_character();
	int get_character_count() const;
	Character_Profile& get_character(int index);
	const Character_Profile& get_character(int index) const;
	void add_character(const Character_Profile&);
private:
	bool contains_character(const String& name);

	// NOTE - main character is at index 0
	Array<Character_Profile> m_characters;
};

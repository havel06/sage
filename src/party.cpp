#include "party.hpp"
#include "character_profile.hpp"
#include "utils/log.hpp"

Party::Party()
{
	// Add placeholder for main character
	m_characters.push_back(Character_Profile{});
}

int Party::get_character_count() const
{
	return m_characters.size();
}

Character_Profile& Party::main_character()
{
	return m_characters[0];
}

Character_Profile& Party::get_character(int index)
{
	return m_characters[index];
}

void Party::add_character(const Character_Profile& profile)
{
	if (contains_character(profile.name)) {
		SG_WARNING("Character \"%s\" is already in party.", profile.name.data());
	} else {
		m_characters.push_back(profile);
	}
}

bool Party::contains_character(const String& name)
{
	for (int i = 0; i < m_characters.size(); i++) {
		if (m_characters[i].name == name)
			return true;
	}

	return false;
}

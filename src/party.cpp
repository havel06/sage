#include "party.hpp"
#include "character_profile.hpp"
#include "utils/log.hpp"

Party::Party(Resource_Handle<Character_Profile> main_character)
{
	m_characters.push_back(main_character);
}

int Party::get_character_count() const
{
	return m_characters.size();
}

Resource_Handle<Character_Profile> Party::main_character() const
{
	return m_characters[0];
}

Resource_Handle<Character_Profile> Party::get_character(int index) const
{
	return m_characters[index];
}


void Party::add_character(Resource_Handle<Character_Profile> profile)
{
	if (contains_character(profile.get().name)) {
		SG_WARNING("Character \"%s\" is already in party.", profile.get().name.data());
	} else {
		m_characters.push_back(profile);
	}
}

bool Party::contains_character(const String& name)
{
	for (int i = 0; i < m_characters.size(); i++) {
		if (m_characters[i].get().name == name)
			return true;
	}

	return false;
}

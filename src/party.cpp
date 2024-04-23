#include "party.hpp"

int Party::get_character_count() const
{
	return m_characters.size();
}

Character_Profile& Party::get_main_character()
{
	return m_characters[0];
}

Character_Profile& Party::get_character(int index)
{
	return m_characters[index];
}

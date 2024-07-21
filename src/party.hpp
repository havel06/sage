#pragma once

#include "character_profile.hpp"
#include "utils/array.hpp"
#include "io/resource/resource_handle.hpp"

class Party
{
public:
	Party(Resource_Handle<Character_Profile> main_character);

	int get_character_count() const;
	Resource_Handle<Character_Profile> get_character(int index) const;
	Resource_Handle<Character_Profile> main_character() const;

	void add_character(Resource_Handle<Character_Profile>);
private:
	bool contains_character(const String& name);

	// NOTE - main character is at index 0
	Array<Resource_Handle<Character_Profile>> m_characters;
};

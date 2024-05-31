#pragma once

#include "ability.hpp"
#include "character_profile.hpp"

class Texture_Manager;
struct cJSON;

class Character_Profile_Loader
{
public:
	Character_Profile_Loader(Texture_Manager&);
	Character_Profile load(const char* file_path);
private:
	Ability load_ability(const cJSON* ability_json);

	Texture_Manager& m_texture_manager;
};

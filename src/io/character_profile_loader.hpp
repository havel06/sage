#pragma once

#include "ability.hpp"
#include "character_profile.hpp"

class Resource_Manager;
struct cJSON;

class Character_Profile_Loader
{
public:
	Character_Profile_Loader(Resource_Manager&);
	Character_Profile load(const char* file_path);
private:
	Ability load_ability(const cJSON* ability_json);

	Resource_Manager& m_resource_manager;
};

#pragma once

#include "character_profile.hpp"

class Resource_Manager;

class Character_Profile_Loader
{
public:
	Character_Profile_Loader(Resource_Manager&);
	Character_Profile load(const char* file_path);
private:
	Resource_Manager& m_resource_manager;
};

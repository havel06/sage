#pragma once

#include "character_profile_manager.hpp"
#include "io/resource/map_manager.hpp"
#include "sequence_manager.hpp"
#include "sound_manager.hpp"
#include "texture_manager.hpp"

class Resource_System
{
public:
	Character_Profile_Manager character_profile_manager;
	Sequence_Manager sequence_manager;
	Sound_Manager sound_manager;
	Texture_Manager texture_manager;
	Map_Manager map_manager;

	Resource_System(const String& resource_root_path, Sequence_Loader&);
};

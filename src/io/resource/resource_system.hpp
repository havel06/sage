#pragma once

#include "character_profile_manager.hpp"
#include "io/gui_loader.hpp"
#include "io/resource/map_manager.hpp"
#include "sequence_manager.hpp"
#include "sound_manager.hpp"
#include "texture_manager.hpp"
#include "font_manager.hpp"

class Resource_System
{
public:
	Texture_Manager texture_manager;
	Font_Manager font_manager;
	Sound_Manager sound_manager;
	GUI_Loader gui_loader;
	Sequence_Manager sequence_manager;
	Character_Profile_Manager character_profile_manager;
	Map_Manager map_manager;

	~Resource_System();

	Resource_System(const String& resource_root_path, Sequence_Loader&, Sequence_Saveloader&);
	void unload_free_resources();
};

#pragma once

#include "character_profile.hpp"
#include "io/character_profile_loader.hpp"
#include "resource_manager.hpp"

class Texture_Manager;
class Sequence_Manager;

class Character_Profile_Manager : public Resource_Manager<Character_Profile>
{
public:
	Character_Profile_Manager(const String& resource_root_path, Texture_Manager&, Sequence_Manager&);
private:
	Own_Ptr<Resource<Character_Profile>> load_resource(const String& filename) override;

	Character_Profile_Loader m_loader;
};

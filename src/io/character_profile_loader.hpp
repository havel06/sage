#pragma once

#include "ability.hpp"
#include "character_profile.hpp"

// fwd
class Texture_Manager;
namespace JSON {
	class Object_View;
}

class Character_Profile_Loader
{
public:
	Character_Profile_Loader(Texture_Manager&);
	Character_Profile load(const char* file_path);
private:
	Ability load_ability(const JSON::Object_View& ability_json);

	Texture_Manager& m_texture_manager;
};

#include "character_profile_manager.hpp"
#include "io/resource/texture_manager.hpp"

Character_Profile_Manager::Character_Profile_Manager(const String& resource_root_path, Texture_Manager& tex_mgr) :
	Resource_Manager(resource_root_path),
	m_loader{tex_mgr}
{
}

Own_Ptr<Character_Profile> Character_Profile_Manager::load_resource(const String& filename)
{
	return make_own_ptr<Character_Profile>(m_loader.load(filename.data()));
}

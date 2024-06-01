#include "sound_manager.hpp"

Sound_Manager::Sound_Manager(const String& resource_root_path) :
	Resource_Manager(resource_root_path)
{
}

Own_Ptr<Sound> Sound_Manager::load_resource(const String& filename)
{
	return make_own_ptr<Sound>(LoadSound(filename.data()));
}
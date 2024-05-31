#include "resource_system.hpp"
#include "io/resource/character_profile_manager.hpp"
#include "io/resource/map_manager.hpp"
#include "io/resource/sequence_manager.hpp"
#include "io/resource/texture_manager.hpp"
#include "io/sequence_loader.hpp"

Resource_System::Resource_System(const String& resource_root_path, Sequence_Loader& seq_loader) :
	character_profile_manager(resource_root_path, texture_manager),
	sequence_manager(resource_root_path, seq_loader),
	sound_manager(resource_root_path),
	texture_manager(resource_root_path),
	map_manager(resource_root_path, *this)
{
}

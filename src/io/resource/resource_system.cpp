#include "resource_system.hpp"
#include "io/resource/character_profile_manager.hpp"
#include "io/resource/map_manager.hpp"
#include "io/resource/sequence_manager.hpp"
#include "io/resource/texture_manager.hpp"
#include "io/sequence/sequence_loader.hpp"
#include "utils/log.hpp"

Resource_System::Resource_System(const String& resource_root_path, Game_Facade& facade, Sequence_Saveloader& saveloader) :
	texture_manager(resource_root_path),
	font_manager(resource_root_path),
	sound_manager(resource_root_path),
	gui_loader{font_manager, texture_manager, resource_root_path},
	sequence_manager(resource_root_path, m_sequence_loader, saveloader),
	character_profile_manager(resource_root_path, texture_manager, sequence_manager),
	map_manager(resource_root_path, *this),
	m_sequence_loader{resource_root_path, *this, facade, gui_loader}
{
}

Resource_System::~Resource_System()
{
	SG_DEBUG("Destroying resource system");
}

void Resource_System::unload_free_resources()
{
	character_profile_manager.unload_free_resources();
	sequence_manager.unload_free_resources();
	sound_manager.unload_free_resources();
	texture_manager.unload_free_resources();
	map_manager.unload_free_resources();
	font_manager.unload_free_resources();
}

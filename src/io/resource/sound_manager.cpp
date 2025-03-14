#include "sound_manager.hpp"
#include "raylib/raylib.h"

Sound_Manager::Sound_Manager(const String& resource_root_path) :
	Resource_Manager(resource_root_path)
{
}

Own_Ptr<Resource<Sound>> Sound_Manager::load_resource(const String& filename)
{
	Sound sound = LoadSound(filename.data());

	if (sound.frameCount == 0) {
		SG_ERROR("Unable to load sound \"%s\".", filename.data());
	}

	return make_own_ptr<Resource<Sound>>(filename, move(sound));
}

bool Sound_Manager::can_unload_resource(const Sound& sound) const
{
	return !IsSoundPlaying(sound);
}

void Sound_Manager::unload_resource(Sound& sound, const String&)
{
	UnloadSound(sound);
}

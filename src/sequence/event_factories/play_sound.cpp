#include "play_sound.hpp"
#include "io/resource/sound_manager.hpp"
#include "utils/own_ptr.hpp"
#include "../events/play_sound.hpp"

namespace Event_Factories {

Play_Sound::Play_Sound(Sound_Manager& sound_mgr) :
	m_sound_manager{sound_mgr}
{
	register_parameter("sound", m_sound_filename);
}

Own_Ptr<Event> Play_Sound::make_event(Game_Facade& facade)
{
	auto sound = m_sound_manager.get(m_sound_filename.value, false);
	return make_own_ptr<Events::Play_Sound>(facade, sound);
}

}

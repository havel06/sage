#include "play_music.hpp"
#include "io/resource/sound_manager.hpp"
#include "utils/own_ptr.hpp"
#include "../events/play_music.hpp"

namespace Event_Factories {

Play_Music::Play_Music(Sound_Manager& sound_mgr) :
	m_sound_manager{sound_mgr}
{
	register_parameter("music", m_music_filename);
}

Own_Ptr<Event> Play_Music::make_event(Game_Facade& facade)
{
	auto sound = m_sound_manager.get(m_music_filename.value, false);
	return make_own_ptr<Events::Play_Music>(facade, sound);
}

}

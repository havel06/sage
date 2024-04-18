#include "play_music.hpp"
#include "game_facade.hpp"

namespace Events
{

Play_Music::Play_Music(Sound music)
{
	m_music = music;
}

void Play_Music::update(Game_Facade& facade, float)
{
	if (!m_activated) {
		facade.play_music(m_music);
		m_activated = true;
	}
}

bool Play_Music::is_finished(Game_Facade&) const
{
	return m_activated;
}

void Play_Music::reset()
{
	m_activated = false;
}

}

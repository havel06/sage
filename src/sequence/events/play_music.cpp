#include "play_music.hpp"
#include "game_facade.hpp"

namespace Events
{

Play_Music::Play_Music(Game_Facade& facade, Sound music) :
	Event{facade}
{
	m_music = music;
}

void Play_Music::update(float)
{
	if (!m_activated) {
		m_game_facade.play_music(m_music);
		m_activated = true;
	}
}

bool Play_Music::is_finished() const
{
	return m_activated;
}

void Play_Music::reset()
{
	m_activated = false;
}

}

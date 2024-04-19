#include "play_sound.hpp"
#include "raylib/raylib.h"

namespace Events
{

Play_Sound::Play_Sound(Game_Facade& facade, Sound sound) :
	Event{facade}
{
	m_sound = sound;
}

void Play_Sound::update(float)
{
	if (!m_activated) {
		PlaySound(m_sound);
		m_activated = true;
	}
}

bool Play_Sound::is_finished() const
{
	return m_activated && !IsSoundPlaying(m_sound);
}

void Play_Sound::reset()
{
	m_activated = false;
}

}
#include "music_player.hpp"
#include "raylib/raylib.h"

void Music_Player::play(Sound new_music)
{
	StopSound(m_current_music);
	PlaySound(new_music);

	m_current_music = new_music;
}

void Music_Player::update()
{
	if (!IsSoundPlaying(m_current_music))
		PlaySound(m_current_music);
}

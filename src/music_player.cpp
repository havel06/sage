#include "music_player.hpp"
#include "raylib/raylib.h"

void Music_Player::play(Sound new_music)
{
	StopSound(m_current_music);
	PlaySound(new_music);

	m_current_music = new_music;
}

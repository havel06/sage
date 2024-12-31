#include "music_player.hpp"
#include "raylib/raylib.h"

void Music_Player::play(Resource_Handle<Sound> new_music)
{
	if (m_current_music.has_value())
		StopSound(m_current_music.value().get());

	PlaySound(new_music.get());
	m_current_music = new_music;
}

void Music_Player::update()
{
	if (!m_current_music.has_value())
		return;

	if (!IsSoundPlaying(m_current_music.value().get()))
		PlaySound(m_current_music.value().get());
}

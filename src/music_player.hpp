#pragma once

#include "raylib/raylib.h"

class Music_Player
{
public:
	void play(Sound);
private:
	Sound m_current_music;
};

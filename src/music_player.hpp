#pragma once

#include "raylib/raylib.h"

class Music_Player
{
public:
	void play(Sound);
	void update();
private:
	Sound m_current_music;
};

#pragma once

#include "io/resource/resource_handle.hpp"
#include "utils/optional.hpp"
#include "raylib/raylib.h"

class Music_Player
{
public:
	void play(Resource_Handle<Sound>);
	void update();
private:
	Optional<Resource_Handle<Sound>> m_current_music;
};

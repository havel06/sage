#pragma once

#include "cJSON.h"
#include "graphics/sprite.hpp"

//fwd
class Resource_Manager;

namespace cJSON_Types
{

Sprite parse_sprite(const cJSON*, Resource_Manager&);

}

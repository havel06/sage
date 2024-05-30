#pragma once

#include "cJSON.h"
#include "graphics/sprite.hpp"
#include "io/tmj.hpp"

//fwd
class Resource_Manager;

namespace cJSON_Types
{

Sprite parse_sprite(const cJSON*, Resource_Manager&);
cJSON* serialise_sprite(const Sprite&, const String& project_dir);

}

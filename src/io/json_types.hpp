#pragma once

#include "utils/json.hpp"
#include "graphics/sprite.hpp"
#include "io/tmj.hpp"

//fwd
class Texture_Manager;

namespace JSON_Types
{

Sprite parse_sprite(const JSON::Object_View&, Texture_Manager&);
cJSON* serialise_sprite(const Sprite&, const String& project_dir); // FIXME - rewrite to use new json wrappers

}

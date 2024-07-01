#pragma once

#include "utils/json.hpp"
#include "graphics/sprite.hpp"
#include "graphics/animated_sprite.hpp"
#include "io/tmj.hpp"

//fwd
class Texture_Manager;

namespace JSON_Types
{

Sprite parse_sprite(const JSON::Object_View&, Texture_Manager&);
JSON::Object serialise_sprite(const Sprite&, const String& project_dir);

Animated_Sprite parse_animated_sprite(const JSON::Object_View&, Texture_Manager&);
JSON::Object serialise_animated_sprite(const Animated_Sprite&, const String& project_dir);

}

#pragma once

#include "utils/json.hpp"

//fwd
class Texture_Manager;
class Animated_Sprite;
class Sprite;
namespace UI {
	struct Size;
}

namespace JSON_Types
{

Sprite parse_sprite(const JSON::Object_View&, Texture_Manager&);
JSON::Object serialise_sprite(const Sprite&, const String& project_dir);

Animated_Sprite parse_animated_sprite(const JSON::Object_View&, Texture_Manager&);
JSON::Object serialise_animated_sprite(const Animated_Sprite&, const String& project_dir);

UI::Size parse_size(const JSON::Object_View& json, const JSON::Object_View& template_params);

}

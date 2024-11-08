#pragma once

#include "graphics/ui/formatted_text.hpp"
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

// FIXME - don't propagate template parameter values, it makes the engine needlessly complicated

Sprite parse_sprite(const JSON::Object_View&, Texture_Manager&);
JSON::Object serialise_sprite(const Sprite&, const String& project_dir);

Animated_Sprite parse_animated_sprite(const JSON::Object_View&, Texture_Manager&);
JSON::Object serialise_animated_sprite(const Animated_Sprite&, const String& project_dir);

Colour parse_colour(const JSON::Object_View& json, const JSON::Object_View& template_params);

UI::Size parse_size(const JSON::Object_View& json, const JSON::Object_View& template_params);
UI::Formatted_Text parse_formatted_text(const JSON::Value_View& json);

}

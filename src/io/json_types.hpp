#pragma once

#include "graphics/game_ui/formatted_text.hpp"
#include "utils/json.hpp"

//fwd
class Texture_Manager;
class Animated_Sprite;
class Sequence_Manager;
struct Battle_Description;
struct Battle_Units_Layout;
class Sprite;
struct Position;
namespace Game_UI {
	struct Size;
}

namespace JSON_Types
{

// FIXME - don't propagate template parameter values, it makes the engine needlessly complicated

Sprite parse_sprite(const JSON::Object_View&, Texture_Manager&);
JSON::Object serialise_sprite(const Sprite&, const String& project_dir);

Animated_Sprite parse_animated_sprite(const JSON::Object_View&, Texture_Manager&);
JSON::Object serialise_animated_sprite(const Animated_Sprite&, const String& project_dir);

Battle_Units_Layout parse_battle_units_layout(const JSON::Object_View& json);
JSON::Object serialise_battle_units_layout(const Battle_Units_Layout&);

Colour parse_colour(const JSON::Object_View& json, const JSON::Object_View& template_params);

Game_UI::Size parse_size(const JSON::Object_View& json, const JSON::Object_View& template_params);
JSON::Object serialise_size(const Game_UI::Size& size);

Game_UI::Formatted_Text parse_formatted_text(const JSON::Value_View& json);

Position parse_position(const JSON::Object_View& json);

}

#include "json_types.hpp"
#include "graphics/animated_sprite.hpp"
#include "graphics/game_ui/formatted_text.hpp"
#include "utils/filesystem.hpp"
#include "io/resource/texture_manager.hpp"
#include "utils/json.hpp"
#include "template.hpp"
#include "graphics/game_ui/size.hpp"
#include "graphics/game_ui/text_align.hpp"
#include "utils/log.hpp"
#include "combat/battle_desc.hpp"
#include "map/position.hpp"

namespace JSON_Types
{

Sprite parse_sprite(const JSON::Object_View& json, Texture_Manager& texture_manager)
{
	const char* texture_name = json["texture"].as_string("");

	if (strlen(texture_name) == 0)
		SG_ERROR("Error when parsing sprite - texture name missing.");

	const Resource_Handle<Sage_Texture> texture = texture_manager.get(texture_name, false);
	Sprite sprite(texture);
	sprite.texture_clip.position.x = json["position_x"].as_int(0);
	sprite.texture_clip.position.y = json["position_y"].as_int(0);
	sprite.texture_clip.size.x = json["size_x"].as_int(texture.get().ray_texture.width);
	sprite.texture_clip.size.y = json["size_y"].as_int(texture.get().ray_texture.height);

	return sprite;
}

JSON::Object serialise_sprite(const Sprite& sprite, const String& project_dir)
{
	assert(!sprite.get_texture_path().empty());

	String texture_relative_path = get_relative_path(sprite.get_texture_path(), project_dir);

	JSON::Object json;
	json.add("texture", texture_relative_path.data());
	json.add("position_x", sprite.texture_clip.position.x);
	json.add("position_y", sprite.texture_clip.position.y);
	json.add("size_x", sprite.texture_clip.size.x);
	json.add("size_y", sprite.texture_clip.size.y);

	return json;
}

Animated_Sprite parse_animated_sprite(const JSON::Object_View& json, Texture_Manager& tex_mgr)
{
	// Fallback for non-animated sprites
	if (!json.has("frame_time")) {
		return Animated_Sprite{parse_sprite(json, tex_mgr)};
	}

	Array<Sprite> frames;

	json["frames"].as_array().for_each([&](const JSON::Value_View& value){
		frames.push_back(parse_sprite(value.as_object(), tex_mgr));
	});

	const float frame_time = json["frame_time"].as_float(1);

	return Animated_Sprite{frames, frame_time};
}

JSON::Object serialise_animated_sprite(const Animated_Sprite& sprite, const String& project_dir)
{
	JSON::Array frames;
	for (const Sprite& frame : sprite.get_frames()) {
		frames.add(JSON::Value{serialise_sprite(frame, project_dir)});
	}

	JSON::Object json;
	json.add("frame_time", JSON::Value{sprite.get_frame_time()});
	json.add("frames", JSON::Value{(JSON::Array&&)frames});

	return json;
}

Game_UI::Size parse_size(const JSON::Object_View& json, const JSON::Object_View& template_params)
{
	Game_UI::Size size;

	if (json.has("automatic")) {
		size.automatic = resolve_templated_value(json["automatic"], template_params).as_bool(false);
		if (size.automatic)
			return size; // We can return immediately, since other values are ignored
	}

	if (json.has("parent_width")) {
		size.parent_width = resolve_templated_value(json["parent_width"], template_params).as_float(0);
	}

	if (json.has("parent_height")) {
		size.parent_height = resolve_templated_value(json["parent_height"], template_params).as_float(0);
	}

	if (json.has("pixels")) {
		size.pixels = resolve_templated_value(json["pixels"], template_params).as_int(0);
	}

	return size;
}

JSON::Object serialise_size(const Game_UI::Size& size)
{
	JSON::Object json;

	json.add("automatic", size.automatic);
	json.add("parent_width", size.parent_width);
	json.add("parent_height", size.parent_height);
	json.add("pixels", size.pixels);

	return json;
}

Colour parse_colour(const JSON::Object_View& json)
{
	return Colour {
		.r = (unsigned char)json["r"].as_int(0),
		.g = (unsigned char)json["g"].as_int(0),
		.b = (unsigned char)json["b"].as_int(0),
		.a = (unsigned char)json["a"].as_int(0)
	};
}

Game_UI::Formatted_Text parse_formatted_text(const JSON::Value_View& json)
{
	Game_UI::Formatted_Text result;

	// Whole text as simple string
	if (json.is_string()) {
		result.fragments.push_back(Game_UI::Formatted_Text_Fragment{
			.text = json.as_string("")
		});
		return result;
	}

	// Array of fragments
	json.as_array().for_each([&](const JSON::Value_View& value){
		// Fragment as simple string
		if (value.is_string()) {
			result.fragments.push_back(Game_UI::Formatted_Text_Fragment{
				.text = value.as_string("")
			});
			return;
		}

		// Parse fragment object
		JSON::Object_View fragment_json = value.as_object();
		Game_UI::Formatted_Text_Fragment fragment;
		fragment.text = fragment_json["text"].as_string("");
		if (fragment_json.has("colour")) {
			fragment.colour = parse_colour(fragment_json["colour"].as_object());
		}

		result.fragments.push_back(move(fragment));
	});

	return result;
}

Position parse_position(const JSON::Object_View& json)
{
	Position result;

	if (json.has("entity")) {
		result.entity_name = String{json.get("entity").as_string("")};
	}

	result.offset.x = json.get("x").as_double(0);
	result.offset.y = json.get("y").as_double(0);

	return result;
}

Battle_Units_Layout parse_battle_units_layout(const JSON::Object_View& json)
{
	auto parse_battle_unit = [](const JSON::Object_View& unit_json) -> Battle_Unit_Placement {
		Battle_Unit_Placement placement;

		placement.position_x = JSON_Types::parse_size(
			unit_json.get("position_x").as_object(), JSON::Object_View{nullptr}
		);
		placement.position_y = JSON_Types::parse_size(
			unit_json.get("position_y").as_object(), JSON::Object_View{nullptr}
		);
		placement.size_x = JSON_Types::parse_size(
			unit_json.get("size_x").as_object(), JSON::Object_View{nullptr}
		);
		placement.size_y = JSON_Types::parse_size(
			unit_json.get("size_y").as_object(), JSON::Object_View{nullptr}
		);

		return placement;
	};

	auto parse_array = [&](Array<Battle_Unit_Placement>& out, const JSON::Array_View& in) {
		in.for_each([&](const JSON::Value_View& value){
			out.push_back(parse_battle_unit(value.as_object()));
		});
	};

	Battle_Units_Layout layout;
	parse_array(layout.heroes, json.get("heroes").as_array());
	parse_array(layout.enemies, json.get("enemies").as_array());
	return layout;
}

JSON::Object serialise_battle_units_layout(const Battle_Units_Layout& layout)
{
	auto serialise_unit = [](const Battle_Unit_Placement& unit) -> JSON::Object {
		JSON::Object unit_json;
		unit_json.add("position_x", serialise_size(unit.position_x));
		unit_json.add("position_y", serialise_size(unit.position_y));
		unit_json.add("size_x", serialise_size(unit.size_x));
		unit_json.add("size_y", serialise_size(unit.size_y));
		return unit_json;
	};

	auto serialise_array = [&](const Array<Battle_Unit_Placement>& array) -> JSON::Array {
		JSON::Array array_json;

		for (const Battle_Unit_Placement& unit : array) {
			array_json.add(serialise_unit(unit));
		}

		return array_json;
	};

	JSON::Object json;
	json.add("heroes", serialise_array(layout.heroes));
	json.add("enemies", serialise_array(layout.enemies));
	return json;
}

Game_UI::Text_Align parse_text_align(const String& str)
{
	if (str == "center")
		return Game_UI::Text_Align::center;
	if (str == "left")
		return Game_UI::Text_Align::left;
	if (str == "right")
		return Game_UI::Text_Align::right;

	SG_ERROR("Unknown align value \"%s\"", str.data());
	return Game_UI::Text_Align::left;
}

}

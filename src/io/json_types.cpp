#include "json_types.hpp"
#include "graphics/animated_sprite.hpp"
#include "utils/filesystem.hpp"
#include "io/resource/texture_manager.hpp"
#include "utils/json.hpp"

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

}

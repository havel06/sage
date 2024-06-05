#include "font_manager.hpp"
#include "raylib/raylib.h"
#include "utils/file.hpp"
#include "utils/own_ptr.hpp"
#include "utils/log.hpp"
#include "utils/json.hpp"

Font_Manager::Font_Manager(const String& resource_root_path) :
	Resource_Manager(resource_root_path)
{
	m_resource_root = resource_root_path;
}

Own_Ptr<Font> Font_Manager::load_resource(const String& filename)
{
	// FIXME - error handling
	JSON::Object json = JSON::Object::from_file(filename.data());
	JSON::Object_View json_view = json.get_view();

	String font_filename = m_resource_root;
	font_filename.append("/");
	font_filename.append(json_view["file"].as_string());

	const int font_size = json_view["size"].as_int();

	Font font = LoadFontEx(font_filename.data(), font_size, nullptr, 0);

	bool filter = json_view["filter"].as_bool();
	if (filter) {
		SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
	}

	return make_own_ptr<Font>(font);
}

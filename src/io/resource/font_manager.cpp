#include "font_manager.hpp"
#include "raylib/raylib.h"
#include "utils/file.hpp"
#include "utils/own_ptr.hpp"
#include "utils/log.hpp"
#include "utils/json.hpp"
#include <string.h>

Font_Manager::Font_Manager(const String& resource_root_path) :
	Resource_Manager(resource_root_path),
	m_default_font{add_internal_resource(make_own_ptr<Resource<Font>>("", GetFontDefault()))}
{
	m_resource_root = resource_root_path;
}

Own_Ptr<Resource<Font>> Font_Manager::load_resource(const String& filename)
{
	JSON::Object json = JSON::Object::from_file(filename.data());
	JSON::Object_View json_view = json.get_view();

	String font_filename = m_resource_root;
	font_filename.append("/");

	const char* file_str = json_view["file"].as_string("");
	if (strlen(file_str) == 0) {
		SG_ERROR("Font file missing.");
	}

	font_filename.append(file_str);

	const int font_size = json_view["size"].as_int(32);

	Font font = LoadFontEx(font_filename.data(), font_size, nullptr, 0);

	if (font.texture.id == GetFontDefault().texture.id) {
		SG_ERROR("Unable to load font file \"%s\".", font_filename.data());
	}

	bool filter = json_view["filter"].as_bool(false);
	if (filter) {
		SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
	}

	return make_own_ptr<Resource<Font>>(filename, move(font));
}

void Font_Manager::unload_resource(Font& font, const String&)
{
	UnloadFont(font);
}

Resource_Handle<Font> Font_Manager::get_default_font()
{
	return m_default_font;
}

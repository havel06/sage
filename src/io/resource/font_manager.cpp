#include "font_manager.hpp"
#include "raylib/raylib.h"
#include "utils/file.hpp"
#include "utils/own_ptr.hpp"
#include "utils/log.hpp"
#include <cJSON.h>

Font_Manager::Font_Manager(const String& resource_root_path) :
	Resource_Manager(resource_root_path)
{
	m_resource_root = resource_root_path;
}

Own_Ptr<Font> Font_Manager::load_resource(const String& filename)
{
	String file_content = read_file_to_str(filename.data());
	cJSON* json = cJSON_Parse(file_content.data());

	String font_filename = m_resource_root;
	font_filename.append("/");
	font_filename.append(cJSON_GetObjectItem(json, "file")->valuestring);
	Font font = LoadFont(font_filename.data());

	bool filter = cJSON_GetObjectItem(json, "filter")->valueint;
	if (filter) {
		SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
	}

	cJSON_Delete(json);

	return make_own_ptr<Font>(font);
}

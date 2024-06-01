#include "font_manager.hpp"
#include "raylib/raylib.h"
#include "utils/own_ptr.hpp"

Font_Manager::Font_Manager(const String& resource_root_path) :
	Resource_Manager(resource_root_path)
{
}

Own_Ptr<Font> Font_Manager::load_resource(const String& filename)
{
	return make_own_ptr<Font>(LoadFont(filename.data()));
}

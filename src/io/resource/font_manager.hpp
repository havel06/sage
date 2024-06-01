#pragma once

#include "resource_manager.hpp"
#include <raylib/raylib.h>

class Font_Manager : public Resource_Manager<Font>
{
public:
	Font_Manager(const String& resource_root_path);
private:
	Own_Ptr<Font> load_resource(const String& filename) override;
};

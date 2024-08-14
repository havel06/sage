#pragma once

#include "io/resource/resource_handle.hpp"
#include "resource_manager.hpp"
#include <raylib/raylib.h>

class Font_Manager : public Resource_Manager<Font>
{
public:
	Font_Manager(const String& resource_root_path);
	Resource_Handle<Font> get_default_font();
private:
	Own_Ptr<Resource<Font>> load_resource(const String& filename) override;
	void unload_resource(Font&, const String& path) override;
	bool can_unload_resource(const Font&) const override { return true; }
	String m_resource_root;

	Resource_Handle<Font> m_default_font;
};

#pragma once

#include "graphics/texture.hpp"
#include "resource_manager.hpp"

class Texture_Manager : public Resource_Manager<Sage_Texture>
{
public:
	Texture_Manager(const String& resource_root_path);
private:
	Own_Ptr<Resource<Sage_Texture>> load_resource(const String& filename) override;
	void unload_resource(Sage_Texture&) override;
	bool can_unload_resource(const Sage_Texture&) const override { return true; }
};

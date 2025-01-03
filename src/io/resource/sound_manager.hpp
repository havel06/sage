#pragma once

#include <raylib/raylib.h>
#include "resource_manager.hpp"

class Sound_Manager : public Resource_Manager<Sound>
{
public:
	Sound_Manager(const String& resource_root_path);
private:
	Own_Ptr<Resource<Sound>> load_resource(const String& filename) override;
	void unload_resource(Sound&, const String&) override;
	bool can_unload_resource(const Sound&) const override;
};

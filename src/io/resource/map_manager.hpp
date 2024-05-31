#pragma once

#include "map/map.hpp"
#include "resource_manager.hpp"

// fwd
class Resource_System;

class Map_Manager : public Resource_Manager<Map>
{
public:
	Map_Manager(const String& resource_root_path, Resource_System& res_system);
private:
	Own_Ptr<Map> load_resource(const String& filename) override;

	Resource_System& m_res_system;
};

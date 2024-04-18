#pragma once

#include "utils/string.hpp"
#include "graphics/sprite.hpp"

class Item_Registry;
class Resource_Manager;
struct cJSON;

class Item_Registry_Loader
{
public:
	Item_Registry_Loader(Resource_Manager&);
	void load(Item_Registry&, String project_root);
private:

	Resource_Manager& m_resource_manager;
};

#pragma once

#include "utils/string.hpp"
#include "graphics/sprite.hpp"

class Item_Registry;
class Texture_Manager;
struct cJSON;

class Item_Registry_Loader
{
public:
	Item_Registry_Loader(Texture_Manager&);
	void load(Item_Registry&, String project_root);
private:

	Texture_Manager& m_texture_manager;
};

#pragma once

#include "utils/string.hpp"

class Map_Entities;
class Entity;

class Dev_Tools_Mode_Entity
{
public:
	//Dev_Tools_Mode_Entity();
	void draw(Map_Entities&);
private:
	void draw_entity_edit();

	Entity* m_selected_entity = nullptr;
};

#pragma once
#include "icon_resource.hpp"
#include "data/icon_data.hpp"
#include "raylib/raylib.h"

namespace Editor_UI
{

class System
{
public:
	// Icons
	const Icon_Resource ICON_SAVE{Icon_Data::ICON_SAVE_DATA, Icon_Data::ICON_SAVE_DATA_SIZE};
	const Icon_Resource ICON_ENTITY{Icon_Data::ICON_ENTITY_DATA, Icon_Data::ICON_ENTITY_DATA_SIZE};
	const Icon_Resource ICON_SEQUENCE{Icon_Data::ICON_SEQUENCE_DATA, Icon_Data::ICON_SEQUENCE_DATA_SIZE};
	const Icon_Resource ICON_ITEMS{Icon_Data::ICON_ITEMS_DATA, Icon_Data::ICON_ITEMS_DATA_SIZE};
	const Icon_Resource ICON_ADD{Icon_Data::ICON_ADD_DATA, Icon_Data::ICON_ADD_DATA_SIZE};
	const Icon_Resource ICON_DELETE{Icon_Data::ICON_DELETE_DATA, Icon_Data::ICON_DELETE_DATA_SIZE};
	const Icon_Resource ICON_MAP{Icon_Data::ICON_MAP_DATA, Icon_Data::ICON_MAP_DATA_SIZE};
	const Icon_Resource ICON_CLOSE{Icon_Data::ICON_CLOSE_DATA, Icon_Data::ICON_CLOSE_DATA_SIZE};
	const Icon_Resource ICON_RELOAD{Icon_Data::ICON_RELOAD_DATA, Icon_Data::ICON_RELOAD_DATA_SIZE};
	const Icon_Resource ICON_INFO{Icon_Data::ICON_INFO_DATA, Icon_Data::ICON_INFO_DATA_SIZE};

	System();
	~System();

	const Font& get_font() const { return m_font; }
private:
	Font m_font;
};

}

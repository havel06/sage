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

	System();
	~System();

	const Font& get_font() const { return m_font; }
private:
	Font m_font;
};

}

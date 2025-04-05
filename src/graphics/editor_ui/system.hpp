#pragma once
#include "icon_resource.hpp"
#include "data/icon_data.hpp"
#include "theme.hpp"
#include "raylib/raylib.h"
#include "context.hpp"

namespace Editor_UI
{

class System
{
public:
	System();
	~System();

	Context create_context();
private:
	Font m_font;
	Theme m_theme;
};

}

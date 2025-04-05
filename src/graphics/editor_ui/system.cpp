#include "system.hpp"
#include "raylib/raylib.h"
#include "data/font_data.hpp"

namespace Editor_UI
{

System::System() :
	m_theme{m_font}
{
	m_font = LoadFontFromMemory(".ttf", Font_Data::FONT_DATA, Font_Data::FONT_DATA_SIZE, 32, nullptr, 0);
	SetTextureFilter(m_font.texture, TEXTURE_FILTER_BILINEAR);
}

System::~System()
{
	UnloadFont(m_font);
}

Context System::create_context()
{
	return Context{m_theme};
}


}

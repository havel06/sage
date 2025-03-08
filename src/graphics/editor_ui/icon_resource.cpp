#include "icon_resource.hpp"

namespace Editor_UI
{

Icon_Resource::Icon_Resource(const unsigned char* data, int size)
{
	Image image = LoadImageFromMemory(".png", data, size);
	m_texture = LoadTextureFromImage(image);
	UnloadImage(image);
}

Icon_Resource::~Icon_Resource()
{
	UnloadTexture(m_texture);
}

}

#pragma once

#include <raylib/raylib.h>

namespace IMGUI
{

class Icon_Resource
{
public:
	Icon_Resource(const unsigned char* data, int size);
	~Icon_Resource();
	const Texture& get() const { return m_texture; }
private:
	Texture m_texture;
};

}

#pragma once

#include "utils/colour.hpp"
#include "icon_data.hpp"
#include <raylib/raylib.h>

// fwd

namespace IMGUI::Theme
{

// Based on #4C566A
const Colour PRIMARY = {170, 199, 255, 255};
const Colour ON_PRIMARY = {10, 48, 95, 255};
const Colour SURFACE = {17, 19, 24, 255};
const Colour ON_SURFACE = {226, 226, 233, 255};
const Colour OUTLINE = {142, 144, 153, 255};

//const int FONT_SIZE_DEFAULT = 14;
const int FONT_SIZE_DEFAULT = 20;
const int PADDING_DEFAULT = 16;

const int ICON_SIZE = 24;

class Icon_Resource
{
public:
	Icon_Resource(const unsigned char* data, int size);
	~Icon_Resource();
	const Texture& get() const { return m_texture; }
private:
	Texture m_texture;
};

struct Default_Icons
{
	const Icon_Resource ICON_SAVE{Icon_Data::ICON_SAVE_DATA, Icon_Data::ICON_SAVE_SIZE};
};

}

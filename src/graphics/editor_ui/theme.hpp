#pragma once

#include "utils/colour.hpp"

// fwd

namespace Editor_UI
{

struct Theme
{
	// Based on material design with base colour #4C566A
	Colour PRIMARY = {170, 199, 255, 255};
	Colour INVERSE_PRIMARY = {65, 95, 145, 255};
	Colour ERROR = {255, 180, 171};
	Colour ON_PRIMARY = {10, 48, 95, 255};
	Colour SURFACE = {17, 19, 24, 255};
	Colour ON_SURFACE = {226, 226, 233, 255};
	Colour OUTLINE = {142, 144, 153, 255};
	Colour OUTLINE_VARIANT = {68, 71, 78, 255};
	Colour SECONDARY_CONTAINER = {62, 71, 89, 255};
	Colour SURFACE_CONTAINER = {29, 32, 36, 255};
	Colour SURFACE_CONTAINER_HIGHEST = {51, 53, 58, 255};
	Colour INVERSE_SURFACE = {226, 226, 233, 255};
	Colour ON_INVERSE_SURFACE = {46, 48, 54, 255};

	Colour FILLED_BUTTON_HOVER = {129, 167, 240, 255}; // NOTE - This doesn't comply with material design
	Colour TRANSPARENT_BUTTON_HOVER = {170, 199, 255, 25};

	int FONT_SIZE_DEFAULT = 16;
	int PADDING_DEFAULT = 16;
	int PADDING_SMALL = 8;
	int ICON_SIZE = 24;
	int NAV_WIDTH = 80;
	int HEADER_HEIGHT = 64;
	int HEADER_HEIGHT_BIG = 80;
};

}

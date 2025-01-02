#pragma once

#include "utils/colour.hpp"

// fwd

namespace Editor_UI::Theme
{

// Based on #4C566A
const Colour PRIMARY = {170, 199, 255, 255};
const Colour INVERSE_PRIMARY = {65, 95, 145, 255};
const Colour ON_PRIMARY = {10, 48, 95, 255};
const Colour SURFACE = {17, 19, 24, 255};
const Colour ON_SURFACE = {226, 226, 233, 255};
const Colour OUTLINE = {142, 144, 153, 255};
const Colour OUTLINE_VARIANT = {68, 71, 78, 255};
const Colour SECONDARY_CONTAINER = {62, 71, 89, 255};
const Colour SURFACE_CONTAINER = {29, 32, 36, 255};
const Colour SURFACE_CONTAINER_HIGHEST = {51, 53, 58, 255};

const Colour FILLED_BUTTON_HOVER = {129, 167, 240, 255}; // NOTE - This doesn't comply with material design
const Colour TRANSPARENT_BUTTON_HOVER = {170, 199, 255, 25};

const int FONT_SIZE_DEFAULT = 16;
const int PADDING_DEFAULT = 16;
const int PADDING_SMALL = 8;
const int ICON_SIZE = 24;
const int NAV_WIDTH = 80;
const int HEADER_HEIGHT = 64;
const int HEADER_HEIGHT_BIG = 80;
}
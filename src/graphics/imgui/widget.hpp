#pragma once

#include "utils/rect.hpp"

namespace IMGUI
{

class Widget
{
public:
	virtual ~Widget() = default;
	virtual void draw() = 0;
	virtual Vec2i layout(Recti bounding_box) = 0; // Returns widget's calculated size
};

}

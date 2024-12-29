#pragma once

#include "utils/rect.hpp"

namespace Editor_UI
{

class Widget
{
public:
	virtual ~Widget() = default;
	virtual void draw(float dt) = 0;
	virtual Vec2i layout(Recti bounding_box) = 0; // Returns widget's calculated size
	virtual void handle_mouse(Vec2i position, bool click) = 0;
	virtual void handle_character(char input) = 0;
	virtual void handle_key(int key) = 0;
};

}

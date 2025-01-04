#pragma once

#include "utils/rect.hpp"

namespace Editor_UI
{

class Widget
{
public:
	virtual ~Widget() = default;
	// Called before layout and draw.
	virtual void update() {}
	// Position the widget and calculate its size. Called before draw, after update.
	// Returns widget's calculated size
	virtual Vec2i layout(Recti bounding_box) = 0;
	// Finally draw the widget, after update and layout.
	virtual void draw(float dt) = 0;

	// Input handling functions
	virtual void handle_mouse(Vec2i position, bool click) { (void)position; (void)click; }
	virtual void handle_character(char input) { (void)input; }
	virtual void handle_key(int key) { (void)key; }
	virtual void handle_scroll(float amount) { (void)amount; }
};

}

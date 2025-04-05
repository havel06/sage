#pragma once

#include "utils/rect.hpp"

namespace Editor_UI
{

struct Theme;

class Widget
{
public:
	virtual ~Widget() = default;
	// Called before layout and draw.
	virtual void update(const Theme& theme) { (void)theme; }
	// Position the widget and calculate its size. Called before draw, after update.
	// Returns widget's calculated size
	virtual Vec2i layout(const Theme& theme, Recti bounding_box) = 0;
	// Finally draw the widget, after update and layout.
	// Widgets are drawn in two passes - one pass for normal widgets
	// and a second pass for overlay widgets (dialog boxes, tooltips etc).
	// This draw is the first pass, where widgets are drawn normally.
	virtual void draw(const Theme& theme, float dt) = 0;
	// Second pass of drawing, for widgets that should be drawn
	// on top of everything else.
	virtual void draw_overlay(const Theme& theme, float dt) = 0;

	// Input handling functions
	virtual void handle_mouse(Vec2i position, bool click) { (void)position; (void)click; }
	virtual void handle_character(char input) { (void)input; }
	virtual void handle_key(int key) { (void)key; }
	virtual void handle_scroll(float amount) { (void)amount; }
};

}

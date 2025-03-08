#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"

// fwd

namespace Editor_UI::Widgets
{

// A widget with a fixed maximum size, but a non-fixed position.
class Dummy : public Widget
{
public:
	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme& theme, float dt) override;
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
private:
};

}

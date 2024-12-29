#pragma once

#include "../widget.hpp"

namespace Editor_UI::Widgets
{

class Divider : public Widget
{
public:
	void draw(float dt) override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override {}
	void handle_character(char) override {}
	void handle_key(int) override {}
private:
	// These are set by layout
	Vec2i m_position;
	int m_width;
};

}

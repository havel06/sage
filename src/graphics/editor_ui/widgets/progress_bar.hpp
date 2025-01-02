#pragma once

#include "../widget.hpp"

namespace Editor_UI::Widgets
{

class Progress_Bar : public Widget
{
public:
	Progress_Bar(float value = 0);

	void set_progress(float value); // Between 0-1
	void draw(float dt) override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override {}
	void handle_character(char) override {}
	void handle_key(int) override {}
private:
	float m_progress = 0;
	// These are set by layout
	Vec2i m_position;
	int m_width;
};

}

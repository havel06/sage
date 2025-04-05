#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"

// fwd

namespace Editor_UI::Widgets
{

// A widget with a fixed maximum size, but a non-fixed position.
class Block : public Widget
{
public:
	Block(Own_Ptr<Widget>&& child, Vec2i max_size);

	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme& theme, float dt) override;
	void update(const Theme& theme) override;
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override;
	void handle_character(char) override;
	void handle_key(int) override;
	void handle_scroll(float amount) override;
private:
	Own_Ptr<Widget> m_child;
	Vec2i m_max_size;
};

}

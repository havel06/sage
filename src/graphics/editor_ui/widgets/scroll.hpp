#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"


namespace Editor_UI::Widgets
{

class Scroll : public Widget
{
public:
	int max_height = 300;
	Scroll(Own_Ptr<Widget>&& child);

	void update(const Theme& theme) override;
	void draw(const Theme&, float dt) override;
	void draw_overlay(const Theme&, float dt) override;
	Vec2i layout(const Theme&, Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override;
	void handle_character(char) override;
	void handle_key(int) override;
	void handle_scroll(float amount) override;
private:
	Recti get_scrollbar_transform();
	void fix_scroll();

	Own_Ptr<Widget> m_child;
	float m_scroll_amount = 0;
	bool m_hover = false;
	Recti m_bounding_box; // Set by layout
	int m_child_height; // Set by layout

	bool m_scrollbar_held = false;
	int m_scrollbar_hold_last_y = 0;
};

}

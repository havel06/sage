#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"


namespace Editor_UI::Widgets
{

class Scroll : public Widget
{
public:
	Scroll(Own_Ptr<Widget>&& child);

	void draw(float dt) override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override;
	void handle_character(char) override;
	void handle_key(int) override;
	void handle_scroll(float amount) override;
private:
	Own_Ptr<Widget> m_child;
	int m_scroll_amount = 0;
	bool m_hover = false;
	Recti m_bounding_box; // Set by layout
	int m_child_height; // Set by layout
};

}

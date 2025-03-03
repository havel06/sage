#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"
#include <raylib/raylib.h>

// fwd

namespace Editor_UI::Widgets
{

class Tooltip : public Widget
{
public:
	Tooltip(Own_Ptr<Widget>&& child, const String& text, const Font& font);

	void draw(const Theme&, float) override;
	void draw_overlay(const Theme& theme, float dt) override;
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override;
	void handle_character(char input) override;
	void handle_key(int key) override;
	void handle_scroll(float amount) override;
private:
	Own_Ptr<Widget> m_child;
	String m_text;
	Font m_font;
	Recti m_bounding_box; // Bounding box of child, set by layout()
	bool m_show = false; // Set by handle_mouse
};

}

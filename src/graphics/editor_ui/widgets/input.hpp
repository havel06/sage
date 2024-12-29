#pragma once

#include "../widget.hpp"
#include "utils/string.hpp"

// fwd
struct Font;

namespace Editor_UI::Widgets
{

class Input : public Widget
{
public:
	// FIXME - encapsulate
	String content = "";
	bool active = true;

	Input(const Font& font, const String& label);
	void draw(float dt) override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override;
	void handle_key(int key) override;
private:
	const Font& m_font;
	String m_label;
	Recti m_bounding_box;
	float m_time_since_cursor_blink = 0;
};

}

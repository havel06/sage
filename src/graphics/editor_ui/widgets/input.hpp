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
	Input(const Font& font, const String& label);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
private:
	const Font& m_font;
	String m_content = "";
	String m_label;
	Recti m_bounding_box;
	bool m_active = false;
};

}

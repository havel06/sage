#pragma once

#include "utils/function_wrapper.hpp"
#include "utils/rect.hpp"
#include "../widget.hpp"
#include "utils/string.hpp"
#include "row.hpp"

// fwd
struct Font;
struct Colour;
namespace Editor_UI {
	class Icon_Resource;
}

namespace Editor_UI::Widgets
{

class Button : public Widget
{
public:
	Function_Wrapper<void()> callback = [](){};
	bool narrow = false; // Narrower padding, for icon buttons
	bool transparent = false; // Transparent background

	// Icon is optional
	Button(const Font& font, const String& label, const Icon_Resource* icon);

	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme&, float) override {}
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override {}
	void handle_key(int) override {}
private:
	int get_horizontal_padding();
	Colour get_background_colour(const Theme& theme);

	const Font& m_font;
	String m_label;
	const Icon_Resource* m_icon = nullptr;
	Recti m_bounding_box;
	bool m_hover = false;
};

}

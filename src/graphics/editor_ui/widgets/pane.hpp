#pragma once
#include "../widget.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "column.hpp"

namespace Editor_UI::Widgets
{

// FIXME - Pane probably doesn't need to be a widget!
class Pane : public Widget
{
public:
	Column column; // Use this to get elements inside pane
	Recti transform;
	Colour colour = Theme::SURFACE;
	Pane(Recti transform, bool padding);
	void update() override;
	void draw(float dt) override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override;
	void handle_key(int) override;
	void handle_scroll(float amount) override;
private:
	bool m_padding = true;
};

}

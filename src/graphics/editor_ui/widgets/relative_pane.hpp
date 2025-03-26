#pragma once

#pragma once
#include "../widget.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "column.hpp"

namespace Editor_UI::Widgets
{

// Pane that will fill all the maximum space
class Relative_Pane : public Widget
{
public:
	// FIXME - only use a single child
	Column column; // Use this to get elements inside pane
	Relative_Pane(bool padding);
	void update() override;
	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme& theme, float dt) override;
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override;
	void handle_key(int) override;
	void handle_scroll(float amount) override;
private:
	bool m_padding = true;
	Recti m_transform; // Calculated by layout()
};

}

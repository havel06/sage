#pragma once
#include "../widget.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "column.hpp"

namespace Editor_UI::Widgets
{

class Dialog : public Widget
{
public:
	// FIXME - use a single child instead of a column
	Column column; // Use this to get elements inside dialog

	Dialog(Vec2i size);

	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme& theme, float dt) override;
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override;
	void handle_key(int) override;
	void handle_scroll(float amount) override;
private:
	Vec2i m_size;
	Vec2i m_position;
};

}

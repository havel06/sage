#pragma once
#include "../widget.hpp"
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
	Pane(Recti transform, bool padding);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
private:
	bool m_padding = true;
	Recti m_transform;
};

}

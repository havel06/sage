#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"

namespace Editor_UI::Widgets
{

// Stack contains multiple widgets and allows switching between them.
class Stack : public Widget
{
public:
	void add_child(Own_Ptr<Widget>&& child);
	void set_current_widget(int index);

	void update() override;
	void draw(float dt) override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override;
	void handle_character(char) override;
	void handle_key(int) override;
	void handle_scroll(float amount) override;
private:
	Array<Own_Ptr<Widget>> m_children;
	int m_current = 0;
};

}

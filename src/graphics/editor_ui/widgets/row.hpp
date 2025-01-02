#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"

namespace Editor_UI::Widgets
{

class Row : public Widget
{
public:
	bool stretch = false; // Items will have maximum distance between them

	void add_child(Own_Ptr<Widget>&&);
	void draw(float dt) override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override;
	void handle_key(int key) override;
	void handle_scroll(float amount) override;
private:
	Vec2i layout_normal(Recti bounding_box);
	Vec2i layout_stretch(Recti bounding_box);

	Array<Own_Ptr<Widget>> m_children;

};

}

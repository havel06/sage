#pragma once

#include "../widget.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"

namespace Editor_UI::Widgets
{

enum class Column_Padding
{
	normal,
	small
};

class Column : public Widget
{
public:
	Column_Padding padding = Column_Padding::normal;

	void clear();
	void add_child(Own_Ptr<Widget>&&);
	void update() override;
	void draw(const Theme&, float dt) override;
	Vec2i layout(const Theme&, Recti bounding_box) override;
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override;
	void handle_key(int key) override;
	void handle_scroll(float amount) override;
private:
	Array<Own_Ptr<Widget>> m_children;

};

}

#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"

namespace Editor_UI::Widgets
{

class Column : public Widget
{
public:
	void add_child(Own_Ptr<Widget>&&);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	Array<Own_Ptr<Widget>> m_children;

};

}

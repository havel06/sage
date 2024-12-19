#pragma once
#include "../widget.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "column.hpp"

namespace IMGUI::Widgets
{

class Pane : public Widget
{
public:
	Column column;
	Pane(Recti transform);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	Recti m_transform;
};

}

#pragma once

#include "utils/rect.hpp"
#pragma once
#include "../widget.hpp"
#include "utils/own_ptr.hpp"
#include "utils/array.hpp"
#include "row.hpp"

namespace IMGUI::Widgets
{

class Button : public Widget
{
public:
	Row row;
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	Recti m_bounding_box;
};

}

#pragma once

#include "../widget.hpp"
#include "utils/string.hpp"

namespace IMGUI::Widgets
{

class Input : public Widget
{
public:
	Input(const String& label);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	String m_label;
	Recti m_bounding_box;
};

}

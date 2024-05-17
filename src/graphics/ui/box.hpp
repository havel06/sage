#pragma once

#include "widget.hpp"
#include "utils/colour.hpp"

namespace UI
{

class Box : public Widget
{
public:
	Colour colour;
private:
	void draw_impl(Recti parent_area, float time_delta) override;
};

}

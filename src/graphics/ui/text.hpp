#pragma once

#include "widget.hpp"
#include "utils/string.hpp"

namespace UI
{

class Text : public Widget
{
public:
	String text;
	int size = 10;
private:
	void draw_impl(Recti parent_area, float time_delta) override;
};

}

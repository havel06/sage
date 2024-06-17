#pragma once

#include "widget.hpp"
#include "utils/string.hpp"
#include "graphics/sprite.hpp"

namespace UI
{

class Image : public Widget
{
public:
	Image(Layout&&, Sprite&&);
private:
	Sprite m_sprite;

	void draw_impl(Recti parent_area, float time_delta) override;
	Widget_Ptr clone_impl(Layout&&) const override;
};

}

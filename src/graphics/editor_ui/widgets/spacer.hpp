#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"

// fwd

namespace Editor_UI::Widgets
{

class Spacer final : public Widget
{
public:
	Spacer(Vec2i size);

	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme& theme, float dt) override;
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
private:
	Vec2i m_size;
};

}

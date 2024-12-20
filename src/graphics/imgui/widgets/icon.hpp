#pragma once

#include "../widget.hpp"
#include "../theme.hpp"

namespace IMGUI::Widgets
{

class Icon : public Widget
{
public:
	Icon(const Theme::Icon_Resource&);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	const Theme::Icon_Resource& m_icon_resource;
	Vec2i m_position; // Calculated by layout
};

}

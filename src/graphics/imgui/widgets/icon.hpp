#pragma once

#include "../widget.hpp"

// fwd
namespace IMGUI
{
	class Icon_Resource;
}

namespace IMGUI::Widgets
{

class Icon : public Widget
{
public:
	Icon(const Icon_Resource&);
	void draw() override;
	Vec2i layout(Recti bounding_box) override;
private:
	const Icon_Resource& m_icon_resource;
	Vec2i m_position; // Calculated by layout
};

}

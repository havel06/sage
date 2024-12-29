#pragma once

#include "../widget.hpp"

// fwd
namespace Editor_UI
{
	class Icon_Resource;
}

namespace Editor_UI::Widgets
{

class Icon : public Widget
{
public:
	Icon(const Icon_Resource&);
	void draw(float dt) override;
	Vec2i layout(Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override {}
	void handle_character(char) override {}
	void handle_key(int) override {}
private:
	const Icon_Resource& m_icon_resource;
	Vec2i m_position; // Calculated by layout
};

}

#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"

// fwd
namespace Editor_UI { class View_Model; }

namespace Editor_UI::Widgets
{

class View_Model_Holder : public Widget
{
public:
	View_Model_Holder(View_Model&);

	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme& theme, float dt) override;
	void update() override;
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override;
	void handle_character(char) override;
	void handle_key(int) override;
	void handle_scroll(float amount) override;
private:
	View_Model& m_view_model;
	Own_Ptr<Widget> m_child;
};

}

#pragma once

#include "../widget.hpp"
#include "utils/own_ptr.hpp"
#include "../state.hpp"

// fwd

namespace Editor_UI::Widgets
{

class Stateful : public Widget
{
public:
	Stateful(Own_Ptr<State>&&);

	void draw(const Theme& theme, float dt) override;
	void draw_overlay(const Theme& theme, float dt) override;
	void update() override;
	Vec2i layout(const Theme& theme, Recti bounding_box) override;
	void handle_mouse(Vec2i, bool) override;
	void handle_character(char) override;
	void handle_key(int) override;
	void handle_scroll(float amount) override;
private:
	Own_Ptr<State> m_state;
	Own_Ptr<Widget> m_child;
};

}

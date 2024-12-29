#pragma once

#include "widgets/pane.hpp"

namespace Editor_UI
{

class Context
{
public:
	void draw(float dt); // Call each frame
	void input_char(char charater);
	void input_key(int key);
	Widgets::Pane& add_pane(Recti transform, bool padding = true);
private:
	Array<Own_Ptr<Widgets::Pane>> m_panes;
};

}

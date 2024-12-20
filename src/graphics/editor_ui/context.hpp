#pragma once

#include "widgets/pane.hpp"

namespace Editor_UI
{

class Context
{
public:
	void draw(); // Call each frame
	Widgets::Pane& add_pane(Recti transform, bool padding = true);
private:
	Array<Own_Ptr<Widgets::Pane>> m_panes;
};

}

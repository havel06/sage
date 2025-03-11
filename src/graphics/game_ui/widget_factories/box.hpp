#pragma once

#include "../widget_factory.hpp"
#include "templating/parameter.hpp"

namespace Game_UI {

class Box_Factory : public Widget_Factory
{
public:
	Box_Factory();
	Own_Ptr<Widget> make_widget(Layout&&) override;
private:
	Colour_Parameter m_colour;
};

}

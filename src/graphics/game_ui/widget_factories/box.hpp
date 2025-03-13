#pragma once

#include "../widget_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/colour_parameter.hpp"

namespace Game_UI {

class Box_Factory : public Widget_Factory
{
public:
	Box_Factory();
	Own_Ptr<Widget> make_widget(Layout&&, const String& name, float fade_in_out_time) override;
private:
	Colour_Parameter m_colour;
};

}

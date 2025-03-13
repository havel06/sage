#pragma once

#include "../widget_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/widget_parameter.hpp"

namespace Game_UI {

class Button_Factory : public Widget_Factory
{
public:
	Button_Factory();
	Own_Ptr<Widget> make_widget(Layout&& layout, const String& name, float fade_in_out_time) override;
private:
	Widget_Parameter m_widget_normal;
	Widget_Parameter m_widget_focused;
};

}

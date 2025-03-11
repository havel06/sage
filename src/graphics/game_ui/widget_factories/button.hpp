#pragma once

#include "../widget_factory.hpp"
#include "templating/parameter.hpp"

namespace Game_UI {

class Button_Factory : public Widget_Factory
{
public:
	Button_Factory();
	Own_Ptr<Widget> make_widget(Layout&& layout) override;
private:
	Widget_Parameter m_widget_normal;
	Widget_Parameter m_widget_focused;
};

}

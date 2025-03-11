#pragma once

#include "../widget_factory.hpp"
#include "templating/parameter.hpp"

namespace Game_UI {

class Image_Factory : public Widget_Factory
{
public:
	Image_Factory();
	Own_Ptr<Widget> make_widget(Layout&& layout) override;
private:
	Sprite_Parameter m_sprite;
};

}

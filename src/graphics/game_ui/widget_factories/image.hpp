#pragma once

#include "../widget_factory.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/sprite_parameter.hpp"
#include "utils/string.hpp"

namespace Game_UI {

class Image_Factory : public Widget_Factory
{
public:
	Image_Factory();
	Own_Ptr<Widget> make_widget(Layout&& layout, const String& name, float fade_in_out_time) override;
private:
	Sprite_Parameter m_sprite;
};

}

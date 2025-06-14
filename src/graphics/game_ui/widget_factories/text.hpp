#pragma once

#include "../widget_factory.hpp"
#include "io/resource/font_manager.hpp"
#include "templating/parameter.hpp"
#include "templating/parameters/formatted_text_parameter.hpp"
#include "templating/parameters/int_parameter.hpp"
#include "templating/parameters/text_align_parameter.hpp"
#include "templating/parameters/colour_parameter.hpp"

namespace Game_UI {

class Text_Factory : public Widget_Factory
{
public:
	Text_Factory(Font_Manager& font_manager);
	Own_Ptr<Widget> make_widget(Layout&& layout, const String& name, float fade_in_out_time) override;
private:
	Font_Manager& m_font_manager;

	String_Parameter m_font;
	Formatted_Text_Parameter m_text;
	Int_Parameter m_size;
	Text_Align_Parameter m_align;
	Colour_Parameter m_colour;
};

}

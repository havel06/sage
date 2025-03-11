#pragma once

#include "../widget_factory.hpp"
#include "templating/parameter.hpp"
#include "io/resource/font_manager.hpp"

namespace Game_UI {

class Text_Factory : public Widget_Factory
{
public:
	Text_Factory(Font_Manager& font_manager);
	virtual Own_Ptr<Widget> make_widget() = 0;
private:
	Font_Manager& m_font_manager;

	String_Parameter m_font;
	Formatted_Text_Parameter m_text;
	Int_Parameter m_size;
	Text_Align_Parameter m_align;
};

}

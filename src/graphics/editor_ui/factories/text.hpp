#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"

// fwd
struct Font;

namespace Editor_UI::Factories
{

class Text final : public Widget_Factory2
{
public:
	Text(const Font& font, const String& text);
	Own_Ptr<Widget> make_widget() override;
private:
	const Font& m_font;
	String m_text;
};

};

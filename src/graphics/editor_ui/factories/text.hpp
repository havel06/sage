#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"

// fwd
struct Font;

namespace Editor_UI::Factories
{

class Text final : public Widget_Factory
{
public:
	static Text* make(const Font& font, const String& text);
	Text(const Font& font, const String& text);
	Own_Ptr<Widget> make_widget() override;
private:
	const Font& m_font;
	String m_text;
};

};

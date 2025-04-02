#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"

// fwd
struct Font;

namespace Editor_UI::Factories
{

class Tooltip final : public Widget_Factory
{
public:
	static Tooltip* make(const String& text, const Font& font, Own_Ptr<Widget_Factory>&& child);
	Tooltip(const String& text, const Font& font, Own_Ptr<Widget_Factory>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	String m_text;
	const Font& m_font;
	Own_Ptr<Widget_Factory> m_child;
};

};

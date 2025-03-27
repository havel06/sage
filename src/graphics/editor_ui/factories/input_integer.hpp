#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"
#include "utils/function_wrapper.hpp"

// fwd
struct Font;

namespace Editor_UI::Factories
{

class Input_Integer final : public Widget_Factory2
{
public:
	static Input_Integer* make(const Font& font, const String& label);
	Input_Integer(const Font& font, const String& label);
	Input_Integer* on_edit(Function_Wrapper<void(int)>&& callback); // Fluent API
	Input_Integer* on_enter(Function_Wrapper<void(int)>&& callback); // Fluent API, triggered when 'enter' is pressed
	Own_Ptr<Widget> make_widget() override;
private:
	const Font& m_font;
	const String m_label;
	Function_Wrapper<void(int)> m_on_edit;
	Function_Wrapper<void(int)> m_on_enter;
};

};

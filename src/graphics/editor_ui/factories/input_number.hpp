#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"
#include "utils/function_wrapper.hpp"

// fwd
struct Font;

namespace Editor_UI::Factories
{

class Input_Number final : public Widget_Factory2
{
public:
	static Input_Number* make(const Font& font, const String& label);
	Input_Number(const Font& font, const String& label);
	Input_Number* on_edit(Function_Wrapper<void(float)>&& callback); // Fluent API
	Input_Number* on_enter(Function_Wrapper<void(float)>&& callback); // Fluent API, triggered when 'enter' is pressed
	Own_Ptr<Widget> make_widget() override;
private:
	const Font& m_font;
	const String m_label;
	Function_Wrapper<void(float)> m_on_edit;
	Function_Wrapper<void(float)> m_on_enter;
};

};

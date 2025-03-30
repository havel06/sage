#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/array.hpp"

// fwd
struct Font;

namespace Editor_UI::Factories
{

class Input_Text final : public Widget_Factory2
{
public:
	static Input_Text* make(const Font& font, const String& label);
	Input_Text(const Font& font, const String& label);
	Input_Text* content(const String& content);
	Input_Text* on_edit(Function_Wrapper<void(const String&)>&& callback); // Fluent API
	Input_Text* on_enter(Function_Wrapper<void(const String&)>&& callback); // Fluent API, triggered when 'enter' is pressed
	Input_Text* with_hints(const Array<String>&); // Fluent API
	Own_Ptr<Widget> make_widget() override;
private:
	const Font& m_font;
	const String m_label;
	String m_default_content;
	Array<String> m_hints;
	Function_Wrapper<void(const String&)> m_on_edit;
	Function_Wrapper<void(const String&)> m_on_enter;
};

};

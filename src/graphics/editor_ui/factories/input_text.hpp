#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/array.hpp"
#include "utils/optional.hpp"

// fwd
struct Font;
namespace Editor_UI::Widgets {
	class Input_State;
}

namespace Editor_UI::Factories
{

class Input_Text final : public Widget_Factory
{
public:
	static Input_Text* make(Widgets::Input_State&, const Font& font, const String& label);
	Input_Text(Widgets::Input_State&, const Font& font, const String& label);
	Input_Text* content(const String& content);
	Input_Text* on_edit(Function_Wrapper<void(const String&)>&& callback); // Fluent API
	Input_Text* on_enter(Function_Wrapper<void(const String&)>&& callback); // Fluent API, triggered when 'enter' is pressed
	Input_Text* with_hints(const Array<String>&); // Fluent API
	Own_Ptr<Widget> make_widget() override;
private:
	Widgets::Input_State& m_state;
	const Font& m_font;
	const String m_label;
	Optional<String> m_default_content;
	Array<String> m_hints;
	Function_Wrapper<void(const String&)> m_on_edit;
	Function_Wrapper<void(const String&)> m_on_enter;
};

};

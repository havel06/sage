#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"
#include "utils/optional.hpp"
#include "utils/function_wrapper.hpp"

// fwd
struct Font;
namespace Editor_UI::Widgets {
	class Input_State;
}


namespace Editor_UI::Factories
{

class Input_Integer final : public Widget_Factory
{
public:
	static Input_Integer* make(Widgets::Input_State&, const Font& font, const String& label);
	Input_Integer(Widgets::Input_State&, const Font& font, const String& label);
	Input_Integer* with_value(int value);
	Input_Integer* on_edit(Function_Wrapper<void(bool valid, int val)>&& callback); // Fluent API
	Input_Integer* on_enter(Function_Wrapper<void(bool valid, int val)>&& callback); // Fluent API, triggered when 'enter' is pressed
	Own_Ptr<Widget> make_widget() override;
private:
	Widgets::Input_State& m_state;
	const Font& m_font;
	const String m_label;
	Optional<int> m_value = {};
	Function_Wrapper<void(bool valid, int value)> m_on_edit;
	Function_Wrapper<void(bool valid, int value)> m_on_enter;
};

};

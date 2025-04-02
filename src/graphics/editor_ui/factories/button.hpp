#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/own_ptr.hpp"
#include "utils/string.hpp"
#include "utils/function_wrapper.hpp"

// fwd
struct Font;
namespace Editor_UI {
	class Icon_Resource;
}

namespace Editor_UI::Factories
{

class Button final : public Widget_Factory
{
public:
	static Button* make(Function_Wrapper<void()>&& callback);
	Button(Function_Wrapper<void()>&& callback);
	Button* with_icon(const Icon_Resource&); // Fluent API
	Button* with_text(const Font& font, const String& text); // Fluent API
	Own_Ptr<Widget> make_widget() override;
private:
	Function_Wrapper<void()> m_callback;
	const Font* m_font = nullptr;
	String m_text;
	const Icon_Resource* m_icon = nullptr;
};

};

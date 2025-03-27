#include "input_text.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Input_Text* Input_Text::make(const Font& font, const String& label)
{
	return new Input_Text(font, label);
}

Input_Text::Input_Text(const Font& font, const String& label) :
	m_font{font},
	m_label{label}
{
}

Input_Text* Input_Text::content(const String& content)
{
	m_default_content = content;
	return this;
}

Input_Text* Input_Text::on_edit(Function_Wrapper<void(const String&)>&& callback)
{
	m_on_edit = move(callback);
	return this;
}

Input_Text* Input_Text::on_enter(Function_Wrapper<void(const String&)>&& callback)
{
	m_on_enter = move(callback);
	return this;
}

Own_Ptr<Widget> Input_Text::make_widget()
{
	auto input = make_own_ptr<Widgets::Input>(m_font, m_label, make_own_ptr<Widgets::Input_Constraint_None>());
	input->on_edit = [this_ptr=input.get(), callback=m_on_edit] () mutable { callback(this_ptr->get_content()); };
	input->on_enter = [this_ptr=input.get(), callback=m_on_enter] () mutable { callback(this_ptr->get_content()); };
	input->set_content(m_default_content);
	return input;
}

}

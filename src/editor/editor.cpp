#include "editor.hpp"
#include "main_widget.hpp"
#include "graphics/editor_ui/factories/stateful.hpp"

namespace Editor
{

Editor::Editor(Editor_UI::System& gui_system, GUI_Loader& gui_loader) :
	m_gui_loader{gui_loader},
	m_context{gui_system.create_context()}
{
	rebuild();
}

void Editor::rebuild()
{
	m_context.set_top_widget(
		Editor_UI::Factories::Stateful::make(
			make_own_ptr<Main_Widget>(m_gui_loader)
		)
	);
}

void Editor::draw(float dt)
{
	m_context.draw(dt);
}

void Editor::input_char(char character)
{
	m_context.input_char(character);
}

void Editor::input_key(int key)
{
	m_context.input_key(key);
}

}

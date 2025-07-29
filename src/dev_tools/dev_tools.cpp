#include "dev_tools.hpp"
#include "graphics/editor_ui/factories/stateful.hpp"
#include "main_widget.hpp"
#include "utils/own_ptr.hpp"

Dev_Tools::Dev_Tools(Editor_UI::System& gui_system, Game_Facade& facade, Game_Logic& logic, Sequence_Manager& seq_mgr, const String& project_root) :
	m_context{gui_system.create_context()},
	m_game_facade{facade},
	m_game_logic{logic},
	m_sequence_manager{seq_mgr},
	m_project_root{project_root}
{
	rebuild();
}

void Dev_Tools::rebuild()
{
	m_context.set_top_widget(
		Editor_UI::Factories::Stateful::make(
			make_own_ptr<Dev_Tools_Main_Widget>(m_game_facade, m_game_logic, m_sequence_manager, m_project_root)
		)
	);
}

void Dev_Tools::draw(float dt)
{
	m_context.draw(dt);
}

void Dev_Tools::input_char(char character)
{
	m_context.input_char(character);
}

void Dev_Tools::input_key(int key)
{
	m_context.input_key(key);
}

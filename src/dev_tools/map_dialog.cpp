#include "map_dialog.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widgets/input.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "game/game_logic_state_normal.hpp"
#include "raylib/raylib.h"
#include "utils/filesystem.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/log.hpp"
#include "utils/string.hpp"
#include "graphics/editor_ui/widgets/dialog.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/input.hpp"

Dev_Tools_Map_Dialog::Dev_Tools_Map_Dialog(const Editor_UI::System& gui, Game_Logic_State_Normal& logic, const String& project_root) :
	m_gui{gui},
	m_logic{logic},
	m_project_root{project_root}
{
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Map_Dialog::build()
{
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();

	if (!m_show)
		return factory.make_text(""); // FIXME - dummy widget?

	auto dialog = factory.make_dialog({400, 300});
	dialog->column.add_child(
		factory.make_icon_button(
			m_gui.ICON_CLOSE,
			[this](){
				m_show = false;	
				m_dirty = true;
			}
		)
	);

	auto input = factory.make_input("Current map");
	input->set_content(get_relative_path(m_logic.get_map_filename(), m_project_root));

	input->on_edit = [this, input=input.get()](){
		m_requested_map = input->get_content();
	};

	dialog->column.add_child(move(input));
	dialog->column.add_child(
		factory.make_button(
			"Change map",
			nullptr,
			[this](){
				m_logic.set_current_map(m_requested_map);
			}
		)
	);

	m_dirty = false;
	return dialog;
}

bool Dev_Tools_Map_Dialog::is_dirty() const
{
	return m_dirty;
}


void Dev_Tools_Map_Dialog::toggle()
{
	m_show = !m_show;
	m_requested_map = "";
	m_dirty = true;
}

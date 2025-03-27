#include "header.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/stateful.hpp"
#include "graphics/editor_ui/widgets/view_model_holder.hpp"
#include "graphics/editor_ui/widgets/tooltip.hpp"
#include "game/game_logic.hpp"
#include "raylib/raylib.h"
#include "utils/move.hpp"
#include "utils/function_wrapper.hpp"

Dev_Tools_Header::Dev_Tools_Header(const Font& font, Game_Facade& facade, Game_Logic& game_logic, const Editor_UI::System& gui, const String& project_root) :
	m_font{font},
	m_game_facade{facade},
	m_game_logic{game_logic},
	m_gui_system{gui},
	m_project_root{project_root}
{
}

void Dev_Tools_Header::close_map_dialog()
{
	m_show_file_dialog = false;
	m_dirty = true;
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Header::build()
{
	Editor_UI::Widget_Factory factory = m_gui_system.get_widget_factory();

	auto map_button = factory.make_icon_button(
		m_gui_system.ICON_MAP,
		[this](){
			m_show_file_dialog = !m_show_file_dialog;
			m_dirty = true;
		}
	);

	auto save_button = factory.make_icon_button(
		m_gui_system.ICON_SAVE,
		[this](){
			m_game_facade.save_game();
		}
	);

	auto load_button = factory.make_icon_button(
		m_gui_system.ICON_RELOAD,
		[this](){
			m_game_logic.continue_game(); // FIXME - is 'continue_game' a good name for the function?
		}
	);

	auto row = factory.make_row();
	row->add_child(factory.make_tooltip(move(map_button), "Change map"));
	row->add_child(factory.make_tooltip(move(save_button), "Save game"));
	row->add_child(factory.make_tooltip(move(load_button), "Load last save"));

	if (m_show_file_dialog) {
		row->add_child(
			make_own_ptr<Editor_UI::Widgets::Stateful>(
				make_own_ptr<Dev_Tools_Map_Dialog>(*this, m_font, m_gui_system, m_game_logic.state_normal, m_project_root)
			)
		);
	}

	m_dirty = false;

	return row;
}

bool Dev_Tools_Header::is_dirty() const
{
	return m_dirty;	
}

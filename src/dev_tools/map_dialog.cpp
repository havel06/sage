#include "map_dialog.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "game/game_logic_state_normal.hpp"
#include "raylib/raylib.h"
#include "utils/filesystem.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/log.hpp"
#include "utils/string.hpp"
#include "header.hpp"
#include "graphics/editor_ui/factories/dummy.hpp"
#include "graphics/editor_ui/factories/dialog.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "graphics/editor_ui/factories/input_text.hpp"

Dev_Tools_Map_Dialog::Dev_Tools_Map_Dialog(Dev_Tools_Header& header, const Font& font, const Editor_UI::System& gui, Game_Logic_State_Normal& logic, const String& project_root) :
	m_header{header},
	m_gui{gui},
	m_logic{logic},
	m_font{font},
	m_project_root{project_root}
{
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Map_Dialog::build()
{
	// FIXME - set dialog hints
	using namespace Editor_UI::Factories;

	m_dirty = false;

	return Dialog::make({400, 300},
		Column::make(Column::Padding::normal)
			->add(Button::make(
				[this](){
					SG_DEBUG("Trigger close button");
					m_header.close_map_dialog();
				})
				->with_icon(m_gui.ICON_CLOSE)
			)
			->add(Input_Text::make(m_font, "Current map")
				->content(get_relative_path(m_logic.get_map_filename(), m_project_root))
				->on_edit([this](const String& content){
					m_requested_map = content;
				})
				->on_enter([this](const String& content){
					m_logic.set_current_map(content);
				})
			)
			->add(Button::make(
				[this](){
					m_logic.set_current_map(m_requested_map);
				})
				->with_text(m_font, "Change map")
			)
	);
}

bool Dev_Tools_Map_Dialog::is_dirty() const
{
	return m_dirty;
}

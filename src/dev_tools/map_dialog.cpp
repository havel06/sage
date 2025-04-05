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

Dev_Tools_Map_Dialog::Dev_Tools_Map_Dialog(Dev_Tools_Header& header, Game_Logic_State_Normal& logic, const String& project_root) :
	m_header{header},
	m_logic{logic},
	m_project_root{project_root}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Map_Dialog::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	m_dirty = false;

	return Dialog::make({400, 300},
		Column::make(Column::Padding::normal)
			->add(Button::make(
				[this](){
					SG_DEBUG("Trigger close button");
					m_header.close_map_dialog();
				})
				->with_icon(theme.ICON_CLOSE)
			)
			->add(Input_Text::make(theme.font, "Current map")
				->content(get_relative_path(m_logic.get_map_filename(), m_project_root))
				->on_edit([this](const String& content){
					m_requested_map = content;
				})
				->on_enter([this](const String& content){
					m_logic.set_current_map(content);
				})
				->with_hints(get_input_hints())
			)
			->add(Button::make(
				[this](){
					m_logic.set_current_map(m_requested_map);
				})
				->with_text(theme.font, "Change map")
			)
	);
}

Array<String> Dev_Tools_Map_Dialog::get_input_hints()
{
	return read_directory_relative(m_project_root);
}

bool Dev_Tools_Map_Dialog::is_dirty() const
{
	return m_dirty;
}

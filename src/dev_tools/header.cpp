#include "game/game_logic.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "graphics/editor_ui/factories/dummy.hpp"
#include "graphics/editor_ui/factories/row.hpp"
#include "graphics/editor_ui/factories/stateful.hpp"
#include "graphics/editor_ui/factories/tooltip.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "header.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/move.hpp"

Dev_Tools_Header::Dev_Tools_Header(Game_Facade& facade, Game_Logic& game_logic, const String& project_root) :
	m_game_facade{facade},
	m_game_logic{game_logic},
	m_project_root{project_root}
{
}

void Dev_Tools_Header::close_map_dialog()
{
	m_show_file_dialog = false;
	m_dirty = true;
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Header::build(const Editor_UI::Theme& theme)
{
	m_dirty = false;

	using namespace Editor_UI::Factories;

	return Row::make(false)
		->add(Tooltip::make("Change map", theme.font, Button::make(
			[this](){
				m_show_file_dialog = !m_show_file_dialog;
				m_dirty = true;
			})
			->with_icon(theme.ICON_MAP)
		))
		->add(Tooltip::make("Save game", theme.font, Button::make(
			[this](){
				m_game_facade.save_game();
			})
			->with_icon(theme.ICON_SAVE)
		))
		->add(Tooltip::make("Load last save", theme.font, Button::make(
			[this](){
				m_game_logic.continue_game(); // FIXME - is 'continue_game' a good name for the function?
			})
			->with_icon(theme.ICON_RELOAD)
		))
		->add(make_dialog_or_dummy());
}

Own_Ptr<Editor_UI::Widget_Factory> Dev_Tools_Header::make_dialog_or_dummy()
{
	using namespace Editor_UI::Factories;

	if (m_show_file_dialog) {
		return Stateful::make(
			make_own_ptr<Dev_Tools_Map_Dialog>(*this, m_game_logic.state_normal, m_project_root)
		);
	} else {
		return Dummy::make();
	}
}

bool Dev_Tools_Header::is_dirty() const
{
	return m_dirty;	
}

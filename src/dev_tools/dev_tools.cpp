#include "dev_tools.hpp"
#include "dev_tools/mode_sequence.hpp"
#include "imgui.h"
#include "utils/log.hpp"
#include "rlImGui.h"
#include "map/map.hpp"
#include "io/user_directory_provider.hpp"
#include "utils/own_ptr.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widgets/nav_rail.hpp"
#include "graphics/editor_ui/widgets/view_model_holder.hpp"
#include "graphics/editor_ui/widgets/stack.hpp"

Dev_Tools::Dev_Tools(User_Directory_Provider& dir_provider, Game_Facade& facade, Game_Logic& logic, Game_Logic_State_Normal& logic_normal, Sequence_Manager& seq_mgr, const Item_Registry& item_reg, Inventory& inv, const String& project_root) :
	m_user_dir_provider{dir_provider},
	m_header(facade, logic, logic_normal, m_gui, project_root),
	m_sequence(m_gui, seq_mgr, project_root),
	m_entity{m_gui},
	m_items(m_gui, item_reg, inv)
{
	rlImGuiSetup(true);

	ImGui::GetIO().IniFilename = NULL;
	ImGui::LoadIniSettingsFromDisk(dir_provider.get_imgui_inifile_path().data());

	// Set up GUI
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();

	// Header
	m_header_pane = &m_context.add_pane(Recti{{0, 0}, {10000, Editor_UI::Theme::HEADER_HEIGHT}});
	m_header_pane->column.add_child(factory.make_view_model_holder(m_header));

	// Nav
	// FIXME - update based on window height????
	auto& nav_pane = m_context.add_pane({{0, Editor_UI::Theme::HEADER_HEIGHT}, {Editor_UI::Theme::NAV_WIDTH, 10000}}, false);
	auto nav_rail = factory.make_nav_rail();
	nav_rail->add_item(
		factory.make_nav_rail_item(
			m_gui.ICON_SEQUENCE,
			"Sequences",
			[this, rail = nav_rail.get()](){
				rail->set_active_index(0);
				m_right_pane_stack->set_current_widget(1);
				m_mode = Dev_Tools_Mode::sequence;
			}
		)
	);
	nav_rail->add_item(
		factory.make_nav_rail_item(
			m_gui.ICON_ENTITY,
			"Entities",
			[this, rail = nav_rail.get()](){
				rail->set_active_index(1);
				m_right_pane_stack->set_current_widget(2);
				m_mode = Dev_Tools_Mode::entities;
			}
		)
	);
	nav_rail->add_item(
		factory.make_nav_rail_item(
			m_gui.ICON_ITEMS,
			"Items",
			[this, rail = nav_rail.get()](){
				rail->set_active_index(2);
				m_right_pane_stack->set_current_widget(0);
				m_mode = Dev_Tools_Mode::items;
			}
		)
	);
	nav_pane.column.add_child(move(nav_rail));

	// Right pane
	m_right_pane = &m_context.add_pane({});

	auto stack = factory.make_stack();
	m_right_pane_stack = stack.get();
	stack->add_child(factory.make_view_model_holder(m_items));
	stack->add_child(factory.make_view_model_holder(m_sequence));
	stack->add_child(factory.make_view_model_holder(m_entity));

	m_right_pane->column.add_child(move(stack));
}

Dev_Tools::~Dev_Tools()
{
	ImGui::SaveIniSettingsToDisk(m_user_dir_provider.get_imgui_inifile_path().data());
	rlImGuiShutdown();
}

void Dev_Tools::draw(float dt)
{
	// Update pane size
	const int RIGHT_PANE_WIDTH = 400;
	m_right_pane->transform =
		{{GetScreenWidth() - RIGHT_PANE_WIDTH, Editor_UI::Theme::HEADER_HEIGHT}, {RIGHT_PANE_WIDTH, GetScreenHeight()}};

	m_context.draw(dt);
}

void Dev_Tools::update(Map& map)
{
	m_sequence.rebuild();
	m_entity.rebuild(map.entities);
}

void Dev_Tools::input_char(char character)
{
	m_context.input_char(character);
}

void Dev_Tools::input_key(int key)
{
	m_context.input_key(key);
}

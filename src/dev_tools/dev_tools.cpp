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

Dev_Tools::Dev_Tools(User_Directory_Provider& dir_provider, Game_Facade& facade, Game_Logic& logic, Sequence_Manager& seq_mgr, const Item_Registry& item_reg, Inventory& inv, const String& project_root) :
	m_user_dir_provider{dir_provider},
	m_general(facade, logic, project_root),
	m_sequence(seq_mgr, project_root),
	m_items(m_gui, item_reg, inv, m_gui.get_font())
{
	rlImGuiSetup(true);

	ImGui::GetIO().IniFilename = NULL;
	ImGui::LoadIniSettingsFromDisk(dir_provider.get_imgui_inifile_path().data());

	// Set up GUI

	// Nav
	// FIXME - refactor building code
	// FIXME - use window height somehow
	auto& nav_pane = m_context.add_pane({{0, 0}, {Editor_UI::Theme::NAV_WIDTH, 10000}}, false);
	auto nav_rail = make_own_ptr<Editor_UI::Widgets::Nav_Rail>();
	nav_rail->add_item(
		make_own_ptr<Editor_UI::Widgets::Nav_Rail_Item>(
			m_gui.get_font(),
			m_gui.ICON_SEQUENCE,
			"Sequences",
			[this, rail = nav_rail.get()](){
				rail->set_active_index(0);
				m_mode = Dev_Tools_Mode::sequence;
			}
		)
	);
	nav_rail->add_item(
		make_own_ptr<Editor_UI::Widgets::Nav_Rail_Item>(
			m_gui.get_font(),
			m_gui.ICON_ENTITY,
			"Entities",
			[this, rail = nav_rail.get()](){
				rail->set_active_index(1);
				m_mode = Dev_Tools_Mode::entities;
			}
		)
	);
	nav_rail->add_item(
		make_own_ptr<Editor_UI::Widgets::Nav_Rail_Item>(
			m_gui.get_font(),
			m_gui.ICON_ITEMS,
			"Items",
			[this, rail = nav_rail.get()](){
				rail->set_active_index(2);
				m_mode = Dev_Tools_Mode::items;
			}
		)
	);
	nav_pane.column.add_child(move(nav_rail));
}

Dev_Tools::~Dev_Tools()
{
	ImGui::SaveIniSettingsToDisk(m_user_dir_provider.get_imgui_inifile_path().data());
	rlImGuiShutdown();
}

void Dev_Tools::draw(Map& map, const String& map_filename)
{
	m_context.draw();

	rlImGuiBegin();
	draw_main_menu();
	switch (m_mode) {
		case Dev_Tools_Mode::general:
			m_general.draw(map_filename);
			break;
		case Dev_Tools_Mode::sequence:
			m_sequence.draw();
			break;
		case Dev_Tools_Mode::entities:
			m_entity.draw(map.entities);
			break;
		case Dev_Tools_Mode::items:
			m_items.draw();
			//m_items.draw();
			break;
	}
	rlImGuiEnd();
}

void Dev_Tools::draw_main_menu()
{
	/*
	ImGui::SetNextWindowPos({0, 0});
	ImGui::SetNextWindowSize({ImGui::GetMainViewport()->Size.x, 0});
	ImGui::Begin("Main menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::BeginTable("Main menu table", 3);
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	if (ImGui::Selectable("General", m_mode == Dev_Tools_Mode::general)) {
		m_mode = Dev_Tools_Mode::general;
	}
	ImGui::TableNextColumn();
	if (ImGui::Selectable("Entities", m_mode == Dev_Tools_Mode::entitiesCallback c)) {
		m_mode = Dev_Tools_Mode::entities;
	}
	ImGui::TableNextColumn();
	if (ImGui::Selectable("Sequences", m_mode == Dev_Tools_Mode::sequence)) {
		m_mode = Dev_Tools_Mode::sequence;
	}
	ImGui::EndTable();
	ImGui::End();
	*/

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::MenuItem("General")) {
			m_mode = Dev_Tools_Mode::general;
		}
		if (ImGui::MenuItem("Entities")) {
			m_mode = Dev_Tools_Mode::entities;
		}
		if (ImGui::MenuItem("Sequence")) {
			m_mode = Dev_Tools_Mode::sequence;
		}
		if (ImGui::MenuItem("Items")) {
			m_mode = Dev_Tools_Mode::items;
		}
		ImGui::EndMainMenuBar();
	}
}

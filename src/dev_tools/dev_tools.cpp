#include "dev_tools.hpp"
#include "dev_tools/mode_sequence.hpp"
#include "graphics/imgui/widgets/input.hpp"
#include "graphics/imgui/widgets/nav_rail.hpp"
#include "imgui.h"
#include "utils/log.hpp"
#include "rlImGui.h"
#include "map/map.hpp"
#include "io/user_directory_provider.hpp"

#include "graphics/imgui/widgets/button.hpp"
#include "graphics/imgui/widgets/icon.hpp"
#include "graphics/imgui/widgets/text.hpp"
#include "graphics/imgui/theme.hpp"
#include "graphics/imgui/widgets/pane.hpp"
#include "utils/own_ptr.hpp"

Dev_Tools::Dev_Tools(User_Directory_Provider& dir_provider, Game_Facade& facade, Game_Logic& logic, Sequence_Manager& seq_mgr, const Item_Registry& item_reg, Inventory& inv, const String& project_root) :
	m_user_dir_provider{dir_provider},
	m_general(facade, logic, project_root),
	m_sequence(seq_mgr, project_root),
	m_items(item_reg, inv)
{
	rlImGuiSetup(true);

	ImGui::GetIO().IniFilename = NULL;
	ImGui::LoadIniSettingsFromDisk(dir_provider.get_imgui_inifile_path().data());
}

Dev_Tools::~Dev_Tools()
{
	ImGui::SaveIniSettingsToDisk(m_user_dir_provider.get_imgui_inifile_path().data());
	rlImGuiShutdown();
}

void Dev_Tools::draw(Map& map, const String& map_filename)
{
	rlImGuiBegin();

	//draw_main_menu();

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
			break;
	}

	rlImGuiEnd();

	// FIXME - remove test code!!!!
	IMGUI::Widgets::Nav_Rail nav_rail;
	nav_rail.add_item(make_own_ptr<IMGUI::Widgets::Nav_Rail_Item>(m_imgui.ICON_SAVE, "Save"));
	nav_rail.add_item(make_own_ptr<IMGUI::Widgets::Nav_Rail_Item>(m_imgui.ICON_SAVE, "Load"));
	nav_rail.add_item(make_own_ptr<IMGUI::Widgets::Nav_Rail_Item>(m_imgui.ICON_SAVE, "Something"));
	IMGUI::Widgets::Pane pane{Recti{Vec2i{200, 100}, Vec2i{200, 400}}};
	auto button = make_own_ptr<IMGUI::Widgets::Button>();
	button->row.add_child(make_own_ptr<IMGUI::Widgets::Text>("Hello", m_imgui.get_font(), IMGUI::Theme::ON_PRIMARY));
	pane.column.add_child(make_own_ptr<IMGUI::Widgets::Text>("This is a line", m_imgui.get_font(), IMGUI::Theme::ON_SURFACE));
	pane.column.add_child(move(button));
	pane.column.add_child(make_own_ptr<IMGUI::Widgets::Text>("Testing!", m_imgui.get_font(), IMGUI::Theme::ON_SURFACE));
	pane.column.add_child(make_own_ptr<IMGUI::Widgets::Icon>(m_imgui.ICON_SAVE));
	String content = "";
	pane.column.add_child(make_own_ptr<IMGUI::Widgets::Input>("Name", content, true));
	pane.layout(Recti{Vec2i{0, 0}, Vec2i{1000, 1000}});
	pane.draw();
	nav_rail.layout(Recti{Vec2i{0, 0}, Vec2i{1000, 1000}});
	nav_rail.draw();
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

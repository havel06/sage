#include "mode_items.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/system.hpp"
#include "item/item_registry.hpp"
#include "item/inventory.hpp"
#include "imgui.h"
#include "raylib/raylib.h"

static const int LIST_PANE_WIDTH = 400;

Dev_Tools_Mode_Items::Dev_Tools_Mode_Items(const Editor_UI::System& system, const Item_Registry& reg, Inventory& inv, const Font& font) :
	m_item_registry{reg},
	m_inventory{inv},
	m_font{font},
	m_gui_system{system}
{
	// Build GUI
	m_pane = &m_context.add_pane({{GetScreenWidth() - LIST_PANE_WIDTH, 0}, {LIST_PANE_WIDTH, GetScreenHeight()}});

	(void)m_inventory;
}

void Dev_Tools_Mode_Items::draw()
{
	rebuild();
	m_context.draw();
}

void Dev_Tools_Mode_Items::rebuild()
{
	// Update pane layout
	m_pane->transform = {{GetScreenWidth() - LIST_PANE_WIDTH, 0}, {LIST_PANE_WIDTH, GetScreenHeight()}};	

	// Build list
	m_pane->column.clear();
	m_item_registry.for_each([&](const Item& item){
		auto row = make_own_ptr<Editor_UI::Widgets::Row>();
		auto label = make_own_ptr<Editor_UI::Widgets::Text>(item.id, m_font, Editor_UI::Theme::ON_SURFACE);
		auto button = make_own_ptr<Editor_UI::Widgets::Button>(m_font, "", &m_gui_system.ICON_ADD);
		button->narrow = true;
		button->transparent = true;
		auto divider = make_own_ptr<Editor_UI::Widgets::Divider>();
		row->add_child(move(label));
		row->add_child(move(button));
		row->stretch = true;
		m_pane->column.add_child(move(row));
		m_pane->column.add_child(move(divider));
	});
}

//void Dev_Tools_Mode_Items::draw()
//{
//	ImGui::Begin("Items", nullptr, ImGuiWindowFlags_NoCollapse);
//
//	m_item_registry.for_each([this](const Item& item){
//		const bool is_selected = m_selected_item == item.id;
//
//		if (ImGui::Selectable(item.name.data(), is_selected)) {
//			m_selected_item = item.id;
//		}
//	});
//
//	if (ImGui::Button("Clear inventory")) {
//		m_inventory.clear();
//	}
//
//	if (ImGui::Button("Add to inventory")) {
//		if (!m_selected_item.empty()) {
//			m_inventory.add_item(m_selected_item, 1);
//		}
//	}
//
//	ImGui::End();
//}

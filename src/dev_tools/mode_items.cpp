#include "mode_items.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "item/item_registry.hpp"
#include "item/inventory.hpp"
#include "imgui.h"

Dev_Tools_Mode_Items::Dev_Tools_Mode_Items(const Item_Registry& reg, Inventory& inv, const Font& font) :
	m_item_registry{reg},
	m_inventory{inv},
	m_font{font}
{
	// Build GUI
	// FIXME - use screen size
	// Build list pane
	const int list_pane_width = 400;
	const int list_pane_height = 5000;
	auto& pane = m_context.add_pane({{1000, 0}, {list_pane_width, list_pane_height}});
	m_column = &pane.column;

	(void)m_inventory;
}

void Dev_Tools_Mode_Items::rebuild()
{
	m_column->clear();
	m_item_registry.for_each([&](const Item& item){
		auto row = make_own_ptr<Editor_UI::Widgets::Row>();
		auto label = make_own_ptr<Editor_UI::Widgets::Text>(item.id, m_font, Editor_UI::Theme::ON_SURFACE);
		row->add_child(move(label));
		m_column->add_child(move(row));
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

#include "mode_sequence.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/widgets/progress_bar.hpp"
#include "io/resource/sequence_manager.hpp"
#include "raylib/raylib.h"
#include "sequence/sequence.hpp"
#include "utils/filesystem.hpp"
#include "utils/log.hpp"
#include "utils/function_wrapper.hpp"

static const int LIST_PANE_WIDTH = 400;

Dev_Tools_Mode_Sequence::Dev_Tools_Mode_Sequence(Editor_UI::System& gui, Sequence_Manager& seq_manager, const String& resource_root_path) :
	m_sequence_manager{seq_manager},
	m_gui{gui},
	m_resource_root{resource_root_path}
{
	m_pane_list = &m_context.add_pane({});
	m_pane_list->column.padding = Editor_UI::Theme::PADDING_SMALL;
	m_pane_detail = &m_context.add_pane({});
}

void Dev_Tools_Mode_Sequence::draw(float dt)
{
	// Update pane layout
	m_pane_list->transform = {{GetScreenWidth() - LIST_PANE_WIDTH, Editor_UI::Theme::HEADER_HEIGHT}, {LIST_PANE_WIDTH, GetScreenHeight() / 2}};
	m_pane_detail->transform =
		{{GetScreenWidth() - LIST_PANE_WIDTH, Editor_UI::Theme::HEADER_HEIGHT + GetScreenHeight() / 2}, {LIST_PANE_WIDTH, GetScreenHeight() / 2}};

	rebuild_list();
	try_rebuild_sequence_edit();
	m_context.draw(dt);
}

void Dev_Tools_Mode_Sequence::rebuild_list()
{
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();
	m_pane_list->column.clear();

	m_sequence_manager.for_each([&](const String& path, Sequence&){
		const String path_relative = get_relative_path(path, m_resource_root);
		auto row = factory.make_row(true);
		row->add_child(factory.make_text(path_relative));
		row->add_child(
			factory.make_icon_button(
				m_gui.ICON_INFO,
				[this, path=path](){
					m_selected_sequence = m_sequence_manager.get(path, true);
				}
			)
		);
		m_pane_list->column.add_child(move(row));
		m_pane_list->column.add_child(factory.make_divider());
	});
}

void Dev_Tools_Mode_Sequence::try_rebuild_sequence_edit()
{
	if (!m_selected_sequence.has_value())
		return;

	Sequence& sequence = m_selected_sequence.value().get();
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();
	m_pane_detail->column.clear();

	auto path_relative = get_relative_path(m_selected_sequence.value().get_path(), m_resource_root);
	m_pane_detail->column.add_child(factory.make_text(path_relative));

	if (sequence.is_active()) {
		m_pane_detail->column.add_child(factory.make_text("State: Active"));
	} else {
		if (sequence.has_finished()) {
			m_pane_detail->column.add_child(factory.make_text("State: Finished"));
		} else {
			m_pane_detail->column.add_child(factory.make_text("State: Inactive"));
		}
	}

	m_pane_detail->column.add_child(factory.make_progress_bar((float)sequence.get_current_event_index() / sequence.get_event_count()));

	m_pane_detail->column.add_child(
		factory.make_button(
			"Reset sequence",
			nullptr,
			[this](){
				Sequence& sequence = m_selected_sequence.value().get();
				sequence.reset();
			}
		)
	);

	m_pane_detail->column.add_child(
		factory.make_button(
			"Activate sequence",
			nullptr,
			[this](){
				Sequence& sequence = m_selected_sequence.value().get();
				sequence.try_activate();
			}
		)
	);
}

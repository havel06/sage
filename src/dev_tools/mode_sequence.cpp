#include "mode_sequence.hpp"
#include "graphics/editor_ui/theme.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
#include "graphics/editor_ui/widgets/row.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"
#include "graphics/editor_ui/widgets/scroll.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/widgets/progress_bar.hpp"
#include "io/resource/sequence_manager.hpp"
#include "raylib/raylib.h"
#include "sequence/sequence.hpp"
#include "utils/filesystem.hpp"
#include "utils/log.hpp"
#include "utils/function_wrapper.hpp"
#include "utils/own_ptr.hpp"

Dev_Tools_Mode_Sequence::Dev_Tools_Mode_Sequence(Editor_UI::System& gui, Sequence_Manager& seq_manager, const String& resource_root_path) :
	m_sequence_manager{seq_manager},
	m_gui{gui},
	m_resource_root{resource_root_path}
{
}


void Dev_Tools_Mode_Sequence::update()
{
	m_dirty = true;
}

bool Dev_Tools_Mode_Sequence::is_dirty() const
{
	return m_dirty;
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Mode_Sequence::build()
{
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();

	auto column = factory.make_column();

	column->add_child(build_list());

	auto edit = try_build_sequence_edit();
	if (edit) {
		column->add_child(factory.make_divider());
		column->add_child(move(edit));
	}

	m_dirty = false;
	return column;
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Mode_Sequence::build_list()
{
	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();
	Own_Ptr<Editor_UI::Widgets::Column> column = factory.make_column();
	column->padding = Editor_UI::Theme::PADDING_SMALL;

	m_sequence_manager.for_each([&](const String& path, Sequence&){
		const String path_relative = get_relative_path(path, m_resource_root);
		auto row = factory.make_row(true);
		row->add_child(factory.make_text(path_relative));
		row->add_child(
			factory.make_icon_button(
				m_gui.ICON_INFO,
				[this, path=path](){
					m_selected_sequence = m_sequence_manager.get(path, true);
					m_dirty = true;
					SG_DEBUG("Click");
				}
			)
		);
		column->add_child(move(row));
		column->add_child(factory.make_divider());
	});

	// Add to main pane
	return factory.make_scroll(move(column));
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Mode_Sequence::try_build_sequence_edit()
{
	if (!m_selected_sequence.has_value())
		return {};

	Sequence& sequence = m_selected_sequence.value().get();

	Editor_UI::Widget_Factory factory = m_gui.get_widget_factory();
	auto column = factory.make_column();

	auto path_relative = get_relative_path(m_selected_sequence.value().get_path(), m_resource_root);
	column->add_child(factory.make_text(path_relative));

	if (sequence.is_active()) {
		column->add_child(factory.make_text("State: Active"));
	} else {
		if (sequence.has_finished()) {
			column->add_child(factory.make_text("State: Finished"));
		} else {
			column->add_child(factory.make_text("State: Inactive"));
		}
	}

	column->add_child(factory.make_progress_bar((float)sequence.get_current_event_index() / sequence.get_event_count()));

	column->add_child(
		factory.make_button(
			"Reset sequence",
			nullptr,
			[this](){
				Sequence& sequence = m_selected_sequence.value().get();
				m_dirty = true;
				sequence.reset();
			}
		)
	);

	column->add_child(
		factory.make_button(
			"Activate sequence",
			nullptr,
			[this](){
				Sequence& sequence = m_selected_sequence.value().get();
				m_dirty = true;
				sequence.try_activate();
			}
		)
	);

	return column;
}

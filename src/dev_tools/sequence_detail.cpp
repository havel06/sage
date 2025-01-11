#include "sequence_detail.hpp"
#include "graphics/editor_ui/widgets/card.hpp"
#include "graphics/editor_ui/widgets/card_type.hpp"
#include "utils/own_ptr.hpp"
#include "utils/function_wrapper.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
#include "graphics/editor_ui/widgets/text.hpp"
#include "graphics/editor_ui/widgets/progress_bar.hpp"
#include "graphics/editor_ui/widgets/button.hpp"
#include "graphics/editor_ui/widgets/divider.hpp"

Dev_Tools_Sequence_Detail::Dev_Tools_Sequence_Detail(
		Editor_UI::System& system,
		const String& resource_root
	) :
	m_system{system},
	m_resource_root{resource_root}
{
}

void Dev_Tools_Sequence_Detail::set_sequence(Resource_Handle<Sequence> sequence)
{
	m_sequence = sequence;
	m_dirty = true;
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Sequence_Detail::build()
{
	auto factory = m_system.get_widget_factory();

	if (!m_sequence.has_value())
		return factory.make_column();

	auto card = factory.make_card(Editor_UI::Widgets::Card_Type::filled);
	auto& column = card->column;

	auto path_relative = get_relative_path(m_sequence.value().get_path(), m_resource_root);
	column.add_child(factory.make_text(path_relative));

	// Active indicator
	if (m_sequence.value().get().is_active()) {
		column.add_child(factory.make_text("State: Active"));
	} else {
		if (m_sequence.value().get().has_finished()) {
			column.add_child(factory.make_text("State: Finished"));
		} else {
			column.add_child(factory.make_text("State: Inactive"));
		}
	}

	// Progress bar
	column.add_child(factory.make_progress_bar(
		(float)m_sequence.value().get().get_current_event_index() / m_sequence.value().get().get_event_count())
	);

	column.add_child(
		factory.make_button(
			"Reset sequence",
			nullptr,
			[this](){
				Sequence& sequence = m_sequence.value().get();
				m_dirty = true;
				sequence.reset();
			}
		)
	);

	column.add_child(
		factory.make_button(
			"Activate sequence",
			nullptr,
			[this](){
				Sequence& sequence = m_sequence.value().get();
				m_dirty = true;
				sequence.try_activate();
			}
		)
	);

	m_dirty = false;
	return card;
}

bool Dev_Tools_Sequence_Detail::is_dirty() const
{
	return m_dirty;
}

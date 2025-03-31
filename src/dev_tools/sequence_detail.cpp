#include "sequence_detail.hpp"
#include "graphics/editor_ui/factories/text.hpp"
#include "utils/own_ptr.hpp"
#include "utils/function_wrapper.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/factories/dummy.hpp"
#include "graphics/editor_ui/factories/column.hpp"
#include "graphics/editor_ui/factories/progress_bar.hpp"
#include "graphics/editor_ui/factories/button.hpp"
#include "graphics/editor_ui/factories/card.hpp"

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

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Sequence_Detail::build()
{
	m_dirty = false;

	using namespace Editor_UI::Factories;

	if (!m_sequence.has_value())
		return Dummy::make();

	auto path_relative = get_relative_path(m_sequence.value().get_path(), m_resource_root);

	return Card::make(Card::Type::filled,
		Column::make(Column::Padding::normal)
			->add(Text::make(m_system.get_font(), path_relative))
			->add(build_active_inidicator())
			->add(build_progress_bar())
			->add(build_reset_button())
			->add(build_activate_button())
	);
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Sequence_Detail::build_active_inidicator()
{
	using namespace Editor_UI::Factories;

	if (m_sequence.value().get().is_active()) {
		return Text::make(m_system.get_font(), "State: Active");
	} else {
		if (m_sequence.value().get().has_finished()) {
			return Text::make(m_system.get_font(), "State: Finished");
		} else {
			return Text::make(m_system.get_font(), "State: Inactive");
		}
	}
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Sequence_Detail::build_progress_bar()
{
	using namespace Editor_UI::Factories;

	const int index = m_sequence.value().get().get_current_event_index();
	const int event_count = m_sequence.value().get().get_event_count();

	const float progress = (float)index / event_count;

	return Progress_Bar::make(progress);
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Sequence_Detail::build_reset_button()
{
	using namespace Editor_UI::Factories;

	auto callback = [this](){
		Sequence& sequence = m_sequence.value().get();
		m_dirty = true;
		sequence.reset();
	};

	return Button::make(callback)
		->with_text(m_system.get_font(), "Reset sequence");
}

Own_Ptr<Editor_UI::Widget_Factory2> Dev_Tools_Sequence_Detail::build_activate_button()
{
	using namespace Editor_UI::Factories;

	auto callback = [this](){
		Sequence& sequence = m_sequence.value().get();
		m_dirty = true;
		sequence.try_activate();
	};

	return Button::make(callback)
		->with_text(m_system.get_font(), "Activate sequence");
}

bool Dev_Tools_Sequence_Detail::is_dirty() const
{
	return m_dirty;
}

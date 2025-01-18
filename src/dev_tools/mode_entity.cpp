#include "mode_entity.hpp"
#include "imgui.h"
#include "map/map.hpp"
#include "utils/log.hpp"
#include "graphics/editor_ui/system.hpp"
#include "graphics/editor_ui/widget_factory.hpp"
#include "graphics/editor_ui/widgets/column.hpp"
#include "graphics/editor_ui/widgets/view_model_holder.hpp"

Dev_Tools_Mode_Entity::Dev_Tools_Mode_Entity(Editor_UI::System& system) :
	m_gui{system},
	m_detail{system},
	m_list{m_detail, system}
{
}

void Dev_Tools_Mode_Entity::rebuild(Map_Entities& entities)
{
	m_list.rebuild(entities, "");
	m_detail.set_entity(nullptr);
	m_dirty = true;
}

Own_Ptr<Editor_UI::Widget> Dev_Tools_Mode_Entity::build()
{
	auto factory = m_gui.get_widget_factory();

	auto column = factory.make_column();

	column->add_child(factory.make_view_model_holder(m_list));
	column->add_child(factory.make_view_model_holder(m_detail));

	m_dirty = false;
	return column;
}

bool Dev_Tools_Mode_Entity::is_dirty() const
{
	return m_dirty;	
}

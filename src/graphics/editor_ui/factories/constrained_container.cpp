#include "constrained_container.hpp"
#include "graphics/editor_ui/widgets/block.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Constrained_Container* Constrained_Container::make(Vec2i max_size, Own_Ptr<Widget_Factory2>&& child)
{
	return new Constrained_Container(max_size, move(child));
}

Constrained_Container::Constrained_Container(Vec2i size, Own_Ptr<Widget_Factory2>&& child) :
	m_max_size{size},
	m_child{move(child)}
{
}

Own_Ptr<Widget> Constrained_Container::make_widget()
{
	return make_own_ptr<Widgets::Block>(m_child->make_widget(), m_max_size);
}

}

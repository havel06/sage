#include "dialog.hpp"
#include "graphics/editor_ui/widgets/dialog.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Own_Ptr<Dialog> Dialog::make(Vec2i size, Own_Ptr<Widget_Factory2>&& child)
{
	return make_own_ptr<Dialog>(size, move(child));
}

Dialog::Dialog(Vec2i size, Own_Ptr<Widget_Factory2>&& child) :
	m_size{size},
	m_child{move(child)}
{
}

Own_Ptr<Widget> Dialog::make_widget()
{
	auto dialog = make_own_ptr<Widgets::Dialog>(m_size);
	dialog->column.add_child(m_child->make_widget());
	return dialog;
}

}

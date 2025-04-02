#include "card.hpp"
#include "graphics/editor_ui/widgets/card.hpp"
#include "graphics/editor_ui/widgets/card_type.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Card* Card::make(Type type, Own_Ptr<Widget_Factory>&& child)
{
	return new Card(type, move(child));
}

Card::Card(Type type, Own_Ptr<Widget_Factory>&& child) :
	m_type{type},
	m_child{move(child)}
{
}

Own_Ptr<Widget> Card::make_widget()
{
	auto card = make_own_ptr<Widgets::Card>(convert_card_type());
	card->column.add_child(m_child->make_widget());
	return card;
}

Widgets::Card_Type Card::convert_card_type()
{
	switch (m_type) {
		case Type::outline:
			return Widgets::Card_Type::outline;
		case Type::filled:
			return Widgets::Card_Type::filled;
	}
}

}

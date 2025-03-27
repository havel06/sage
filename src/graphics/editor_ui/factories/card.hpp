#pragma once

#include "graphics/editor_ui/widget_factory2.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"

// fwd
namespace Editor_UI::Widgets {
	enum class Card_Type;
}

namespace Editor_UI::Factories
{

class Card final : public Widget_Factory2
{
public:
	enum class Type {
		outline,
		filled
	};

	static Own_Ptr<Card> make(Type type, Own_Ptr<Widget_Factory2>&& child);
	Card(Type type, Own_Ptr<Widget_Factory2>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	Widgets::Card_Type convert_card_type();

	Type m_type;
	Own_Ptr<Widget_Factory2> m_child;
};

};

#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/vec2.hpp"
#include "utils/own_ptr.hpp"

// fwd
namespace Editor_UI::Widgets {
	class Scroll_State;
}

namespace Editor_UI::Factories
{

class Scroll final : public Widget_Factory
{
public:
	static Scroll* make(Widgets::Scroll_State&, Own_Ptr<Widget_Factory>&& child);
	Scroll(Widgets::Scroll_State&, Own_Ptr<Widget_Factory>&& child);
	Own_Ptr<Widget> make_widget() override;
private:
	Widgets::Scroll_State& m_state;
	Own_Ptr<Widget_Factory> m_child;
};

};

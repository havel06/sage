#pragma once

#include "graphics/editor_ui/widget_factory.hpp"
#include "utils/own_ptr.hpp"
#include "../state.hpp"

// fwd
namespace Editor_UI {
	class Icon_Resource;
}

namespace Editor_UI::Factories
{

class Stateful final : public Widget_Factory
{
public:
	static Stateful* make(Own_Ptr<State>&&);
	Stateful(Own_Ptr<State>&&);
	Own_Ptr<Widget> make_widget() override;
private:
	Own_Ptr<State> m_state;
};

};

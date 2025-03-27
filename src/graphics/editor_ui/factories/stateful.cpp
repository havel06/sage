#include "stateful.hpp"
#include "graphics/editor_ui/widgets/stateful.hpp"
#include "utils/own_ptr.hpp"
#include "utils/move.hpp"

namespace Editor_UI::Factories
{

Stateful* Stateful::make(Own_Ptr<State>&& state)
{
	return new Stateful(move(state));
}

Stateful::Stateful(Own_Ptr<State>&& state) :
	m_state{move(state)}
{
}

Own_Ptr<Widget> Stateful::make_widget()
{
	return make_own_ptr<Widgets::Stateful>(move(m_state));
}

}

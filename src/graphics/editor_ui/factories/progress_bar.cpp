#include "progress_bar.hpp"
#include "graphics/editor_ui/widgets/progress_bar.hpp"
#include "utils/move.hpp"
#include "utils/own_ptr.hpp"

namespace Editor_UI::Factories
{

Progress_Bar::Progress_Bar(float progress) :
	m_progress{progress}
{
}

Own_Ptr<Widget> Progress_Bar::make_widget()
{
	return make_own_ptr<Widgets::Progress_Bar>(m_progress);
}

}

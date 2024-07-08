#include "show_gui.hpp"
#include "graphics/ui/layout.hpp"
#include "io/gui_loader.hpp"
#include "utils/own_ptr.hpp"
#include "../events/show_gui.hpp"
#include "utils/move.hpp"

namespace Event_Factories {

Show_GUI::Show_GUI(GUI_Loader& gui_loader) :
	m_gui_loader{gui_loader}
{
	register_parameter("widget", m_widget_filename);
}

Own_Ptr<Event> Show_GUI::make_event(Game_Facade& facade)
{
	UI::Widget_Ptr widget = m_gui_loader.load(m_widget_filename.value);
	return make_own_ptr<Events::Show_GUI>(facade, move(widget));
}

}

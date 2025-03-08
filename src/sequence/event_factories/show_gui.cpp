#include "show_gui.hpp"
#include "io/gui_loader.hpp"
#include "utils/own_ptr.hpp"
#include "../events/show_gui.hpp"
#include "utils/move.hpp"

namespace Event_Factories {

Show_GUI::Show_GUI()
{
	register_parameter("widget", m_widget_filename);
}

Own_Ptr<Event> Show_GUI::make_event(Game_Facade& facade)
{
	return make_own_ptr<Events::Show_GUI>(facade, m_widget_filename.value);
}

}

#include "mode_gui.hpp"
#include "mode_gui_open_dialog.hpp"
#include "io/gui_loader.hpp"

#include "graphics/editor_ui/factories/stateful.hpp"

namespace Editor
{

Mode_GUI::Mode_GUI(GUI_Loader& gui_loader) :
	m_gui_loader{gui_loader}
{
}

Own_Ptr<Editor_UI::Widget_Factory> Mode_GUI::build(const Editor_UI::Theme& theme)
{
	using namespace Editor_UI::Factories;

	m_dirty = false;

	if (m_widget) {
		return build_editor(theme);
	} else {
		return Stateful::make(make_own_ptr<Mode_GUI_Open_Dialog>(*this));
	}
}

void Mode_GUI::open_widget(const String& relative_path)
{
	m_widget = m_gui_loader.load_factory(relative_path);
	m_dirty = true;
}

Own_Ptr<Editor_UI::Widget_Factory> Mode_GUI::build_editor(const Editor_UI::Theme& theme)
{
	// FIXME
	(void)theme;
	return nullptr;
}

}

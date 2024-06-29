#include "main_menu_renderer.hpp"
#include "ui/widget.hpp"
#include "ui/text.hpp"
#include "ui/button.hpp"
#include "io/gui_loader.hpp"
#include "utils/log.hpp"

void Main_Menu_Renderer::load(GUI_Loader& loader, const String& project_root)
{
	String menu_path = project_root;
	menu_path.append("/main_menu.json");
	m_widget = loader.load(menu_path.data());

	String button_path = project_root;
	button_path.append("/main_menu_button.json");
	auto button_widget = loader.load(button_path.data());

	UI::Widget* options_box = (m_widget->get_widget_by_name("Options"));
	options_box->clear_children();

	auto add_option = [&](const String& name, auto callback) {
		UI::Widget_Ptr option_widget = button_widget->clone();

		// FIXME - safe cast
		((UI::Text*)(option_widget->get_widget_by_name("Name")))->text = name;
		((UI::Button*)(option_widget->get_widget_by_name("Button")))->on_click = callback;

		options_box->add_child((UI::Widget_Ptr&&)option_widget);
	};

	add_option("Continue", [](){});
	add_option("New Game", [](){});
	add_option("Exit", [](){});

	m_widget->focus_first();
}

void Main_Menu_Renderer::draw(float dt)
{
	m_widget->draw_as_root(dt);
}

void Main_Menu_Renderer::input_direction(Direction direction)
{
	m_widget->move_focus(direction);
}

void Main_Menu_Renderer::enter()
{
	m_widget->process_click();
}

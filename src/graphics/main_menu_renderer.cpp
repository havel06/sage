#include "main_menu_renderer.hpp"
#include "ui/widget.hpp"
#include "ui/text.hpp"
#include "ui/button.hpp"
#include "io/gui_loader.hpp"
#include "utils/log.hpp"
#include "game/game_logic.hpp"

Main_Menu_Renderer::Main_Menu_Renderer(Game_Logic& logic) :
	m_logic{logic}
{
}

void Main_Menu_Renderer::load(GUI_Loader& loader, const String& menu_filename, const String& option_filename)
{
	if (menu_filename.empty() || option_filename.empty())
		return;
	
	m_widget = loader.load(menu_filename);
	auto button_widget = loader.load(option_filename);

	UI::Widget* options_box = (m_widget->get_widget_by_name("Options"));
	options_box->clear_children();

	auto add_option = [&](const String& name, auto callback) {
		UI::Widget_Ptr option_widget = button_widget->clone();

		// FIXME - safe cast
		((UI::Text*)(option_widget->get_widget_by_name("Name")))->text = name;
		((UI::Button*)(option_widget->get_widget_by_name("Button")))->on_click = callback;

		options_box->add_child((UI::Widget_Ptr&&)option_widget);
	};

	add_option("Continue", [this](){
		m_logic.continue_game();
	});

	add_option("New Game", [this](){
		m_logic.new_game();
	});

	add_option("Exit", [this](){
		m_logic.exit_game();
	});

	m_widget->focus_first();
	m_widget->show(true);
}

void Main_Menu_Renderer::draw(float dt)
{
	if (!m_widget)
		return;

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

#include "main_menu_renderer.hpp"
#include "game_ui/box.hpp"
#include "game_ui/layout.hpp"
#include "game_ui/size.hpp"
#include "game_ui/widget_visitor.hpp"
#include "game_ui/widget.hpp"
#include "game_ui/text.hpp"
#include "game_ui/button.hpp"
#include "io/gui_loader.hpp"
#include "utils/log.hpp"
#include "game/game_logic.hpp"

Main_Menu_Renderer::Main_Menu_Renderer(Game_Logic& logic, Resource_Handle<Font> default_font) :
	m_logic{logic},
	m_default_font{default_font}
{
}

void Main_Menu_Renderer::load(GUI_Loader& loader, const String& menu_filename, const String& option_filename)
{
	if (menu_filename.empty() || option_filename.empty()) {
		use_fallback_widgets();
		return;
	}
	
	auto main_widget = loader.load(menu_filename);
	auto button_widget = loader.load(option_filename);
	init_widgets(move(main_widget), button_widget);
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

void Main_Menu_Renderer::init_widgets(Game_UI::Widget_Ptr&& main_widget, Game_UI::Widget_Ptr& option_widget)
{
	m_widget = move(main_widget);

	Game_UI::Widget* options_box = (m_widget->get_widget_by_name("Options"));
	if (!options_box)
		return;

	options_box->clear_children();

	auto add_option = [&](const String& name, auto callback) {
		Game_UI::Widget_Ptr new_widget = option_widget->clone();

		Game_UI::Widget* name_widget = new_widget->get_widget_by_name("Name");
		Game_UI::Widget* button_widget = new_widget->get_widget_by_name("Button");

		if (!name_widget || !button_widget)
			return;

		Game_UI::Text_Widget_Visitor name_visitor{[&](Game_UI::Text& text){
			text.text = name;
		}};

		Game_UI::Button_Widget_Visitor button_visitor{[&](Game_UI::Button& button){
			button.on_click = callback;
		}};

		name_widget->accept_visitor(name_visitor);
		button_widget->accept_visitor(button_visitor);

		options_box->add_child((Game_UI::Widget_Ptr&&)new_widget);
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

void Main_Menu_Renderer::use_fallback_widgets()
{
	// Main widget layout
	Array<Game_UI::Size> layout_rows;
	layout_rows.push_back(Game_UI::Size{
		.pixels = 40
	});

	Array<Game_UI::Size> layout_columns;
	layout_columns.push_back(Game_UI::Size{
		.parent_width = 1
	});

	Game_UI::Layout main_widget_layout{
		move(layout_rows),
		move(layout_columns)
	};

	// Main widget
	Game_UI::Widget_Ptr main_widget = make_own_ptr<Game_UI::Box>(move(main_widget_layout));
	main_widget->set_name("Options");

	// Button widget - unfocused
	Game_UI::Widget_Ptr button_normal = make_own_ptr<Game_UI::Box>(Game_UI::Layout{});

	// Button widget - focused
	Own_Ptr<Game_UI::Box> button_focused = make_own_ptr<Game_UI::Box>(Game_UI::Layout{});
	button_focused->colour = Colour{100, 100, 100, 255};

	// Button widget
	Game_UI::Widget_Ptr button_widget =
		make_own_ptr<Game_UI::Button>(move(button_normal), move(button_focused), Game_UI::Layout{});
	button_widget->set_name("Button");

	// Buttont text widget
	Own_Ptr<Game_UI::Text> text_widget = make_own_ptr<Game_UI::Text>(m_default_font, Game_UI::Layout{});
	text_widget->set_name("Name");
	text_widget->size = 32;
	button_widget->add_child(move(text_widget));

	init_widgets(move(main_widget), button_widget);
}

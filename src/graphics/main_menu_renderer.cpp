#include "main_menu_renderer.hpp"
#include "graphics/ui/box.hpp"
#include "graphics/ui/layout.hpp"
#include "graphics/ui/size.hpp"
#include "ui/widget.hpp"
#include "ui/text.hpp"
#include "ui/button.hpp"
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

void Main_Menu_Renderer::init_widgets(UI::Widget_Ptr&& main_widget, UI::Widget_Ptr& option_widget)
{
	m_widget = move(main_widget);

	UI::Widget* options_box = (m_widget->get_widget_by_name("Options"));
	options_box->clear_children();

	auto add_option = [&](const String& name, auto callback) {
		UI::Widget_Ptr button_widget = option_widget->clone();

		// FIXME - safe cast
		((UI::Text*)(button_widget->get_widget_by_name("Name")))->text = name;
		((UI::Button*)(button_widget->get_widget_by_name("Button")))->on_click = callback;

		options_box->add_child((UI::Widget_Ptr&&)button_widget);
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
	Array<UI::Size> layout_rows;
	layout_rows.push_back(UI::Size{
		.pixels = 40
	});

	Array<UI::Size> layout_columns;
	layout_columns.push_back(UI::Size{
		.parent_width = 1
	});

	UI::Layout main_widget_layout{
		move(layout_rows),
		move(layout_columns)
	};

	// Main widget
	UI::Widget_Ptr main_widget = make_own_ptr<UI::Box>(move(main_widget_layout));
	main_widget->set_name("Options");

	// Button widget - unfocused
	UI::Widget_Ptr button_normal = make_own_ptr<UI::Box>(UI::Layout{});

	// Button widget - focused
	Own_Ptr<UI::Box> button_focused = make_own_ptr<UI::Box>(UI::Layout{});
	button_focused->colour = Colour{100, 100, 100, 255};

	// Button widget
	UI::Widget_Ptr button_widget =
		make_own_ptr<UI::Button>(move(button_normal), move(button_focused), UI::Layout{});
	button_widget->set_name("Button");

	// Buttont text widget
	Own_Ptr<UI::Text> text_widget = make_own_ptr<UI::Text>(m_default_font, UI::Layout{});
	text_widget->set_name("Name");
	text_widget->size = 32;
	button_widget->add_child(move(text_widget));

	init_widgets(move(main_widget), button_widget);
}

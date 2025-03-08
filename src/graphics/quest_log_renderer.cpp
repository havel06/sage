#include "quest_log_renderer.hpp"
#include "graphics/game_ui/widget_visitor.hpp"
#include "quest/quest_log.hpp"
#include "io/gui_loader.hpp"
#include "game_ui/box.hpp"
#include "game_ui/text.hpp"

Quest_Log_Renderer::Quest_Log_Renderer(const Quest_Log& log) :
	m_quest_log{log}
{
}

void Quest_Log_Renderer::load(GUI_Loader& gui_loader, const String& questlog_filename, const String& quest_filename)
{
	if (quest_filename.empty() || quest_filename.empty())
		return;


	m_log_widget = gui_loader.load(questlog_filename);
	m_quest_widget = gui_loader.load(quest_filename);
}

void Quest_Log_Renderer::show(bool value)
{
	if (!m_log_widget)
		return;

	m_log_widget->show(value);
}

void Quest_Log_Renderer::draw(float dt)
{
	if (!m_log_widget || !m_quest_widget)
		return;

	Game_UI::Widget* quests_box_widget = m_log_widget->get_widget_by_name("Quests");
	if (!quests_box_widget)
		return;

	// Put the quests in
	quests_box_widget->clear_children();
	for (int i = 0; i < m_quest_log.get_quest_count(); i++) {
		Game_UI::Widget_Ptr new_quest_widget = m_quest_widget->clone();

		Game_UI::Widget* quest_name = new_quest_widget->get_widget_by_name("Name");
		Game_UI::Widget* quest_desc = new_quest_widget->get_widget_by_name("Description");

		if (!quest_name || !quest_desc)
			continue;

		Game_UI::Text_Widget_Visitor name_visitor{[&](Game_UI::Text& text){
			text.text = m_quest_log.get_quest(i).name;;
		}};

		Game_UI::Text_Widget_Visitor description_visitor{[&](Game_UI::Text& text){
			text.text = m_quest_log.get_quest(i).description;;
		}};

		quest_name->accept_visitor(name_visitor);
		quest_desc->accept_visitor(description_visitor);

		quests_box_widget->add_child((Game_UI::Widget_Ptr&&)new_quest_widget);
	}

	m_log_widget->draw_as_root(dt);
}

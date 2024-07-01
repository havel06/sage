#include "quest_log_renderer.hpp"
#include "quest/quest_log.hpp"
#include "io/gui_loader.hpp"
#include "ui/box.hpp"
#include "ui/text.hpp"

Quest_Log_Renderer::Quest_Log_Renderer(const Quest_Log& log) :
	m_quest_log{log}
{
}

void Quest_Log_Renderer::load(GUI_Loader& gui_loader, const String& project_root, const String& questlog_filename, const String& quest_filename)
{
	if (quest_filename.empty() || quest_filename.empty())
		return;

	String log_path = project_root;
	log_path.append("/");
	log_path.append(questlog_filename);

	String quest_path = project_root;
	quest_path.append("/");
	quest_path.append(quest_filename);

	m_log_widget = gui_loader.load(log_path.data());
	m_quest_widget = gui_loader.load(quest_path.data());
}

void Quest_Log_Renderer::draw()
{
	if (!m_log_widget || !m_quest_widget)
		return;

	// FIXME - do this cast safely
	UI::Box* quests_box_widget = (UI::Box*)m_log_widget->get_widget_by_name("Quests");
	assert(quests_box_widget);

	// Put the quests in
	quests_box_widget->clear_children();
	for (int i = 0; i < m_quest_log.get_quest_count(); i++) {
		UI::Widget_Ptr new_quest_widget = m_quest_widget->clone();
		// FIXME - do this cast safely
		UI::Text* quest_name = (UI::Text*)new_quest_widget->get_widget_by_name("Name");
		UI::Text* quest_desc = (UI::Text*)new_quest_widget->get_widget_by_name("Description");

		assert(quest_name);
		assert(quest_desc);
		quest_name->text = m_quest_log.get_quest(i).name;
		quest_desc->text = m_quest_log.get_quest(i).description;

		quests_box_widget->add_child((UI::Widget_Ptr&&)new_quest_widget);
	}

	m_log_widget->draw_as_root(0);
}

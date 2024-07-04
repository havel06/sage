#include "text_box_renderer.hpp"
#include "io/gui_loader.hpp"
#include "text_box.hpp"
#include "raylib/raylib.h"
#include "ui/text.hpp"

Text_Box_Renderer::Text_Box_Renderer(const Text_Box& text_box) :
	m_text_box{text_box}
{
}

void Text_Box_Renderer::load(GUI_Loader& gui_loader, const String& filename)
{
	if (filename.empty())
		return;

	m_widget = gui_loader.load(filename.data());
}

void Text_Box_Renderer::draw(float time_delta)
{
	if (!m_widget)
		return;

	m_widget->show(m_text_box.contains_message());

	if (!m_widget->is_showing())
		return;

	if (m_text_box.contains_message()) {
		assert(m_widget);
		// FIXME - do this cast safely
		UI::Text* text_widget = (UI::Text*)m_widget->get_widget_by_name("Text");
		assert(text_widget);

		text_widget->text = m_text_box.get_displayed_message().substring(0, m_text_box.get_displayed_character_count());
	}

	m_widget->draw_as_root(time_delta);
}

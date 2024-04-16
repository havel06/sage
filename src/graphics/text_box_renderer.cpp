#include "text_box_renderer.hpp"
#include "text_box.hpp"
#include "raylib/raylib.h"

Text_Box_Renderer::Text_Box_Renderer(const Text_Box& text_box) :
	m_text_box{text_box}
{
}

void Text_Box_Renderer::draw()
{
	if (!m_text_box.contains_message())
		return;

	// Background
	const int margin = 10;
	const int width = GetScreenWidth() - margin * 2;
	const int height = 300;

	const int pos_x = margin;
	const int pos_y = GetScreenHeight() - height - margin;

	const Color background_colour = Color{0, 0, 0, 200};

	DrawRectangle(pos_x, pos_y, width, height, background_colour);

	// Text
	const int padding = 10;
	const int font_size = 20;
	const int text_pos_x = pos_x + padding;
	const int text_pos_y = pos_y + padding;
	DrawText(
		m_text_box.get_displayed_message().data(),
		text_pos_x,
		text_pos_y,
		font_size,
		WHITE);
}

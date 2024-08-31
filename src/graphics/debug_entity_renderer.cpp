#include "debug_entity_renderer.hpp"
#include "map/map.hpp"
#include "map/entity.hpp"
#include "camera.hpp"
#include <raylib/raylib.h>

Debug_Entity_Renderer::Debug_Entity_Renderer(const Game_Camera& cam) :
	m_camera{cam}
{
}

void Debug_Entity_Renderer::draw(const Map_Entities& entities)
{
	for (int i = 0; i < entities.get_entity_count(); i++) {
		draw_entity(entities.get_entity(i));
	}
}

void Debug_Entity_Renderer::draw_entity(const Entity& entity)
{
	BeginMode2D(m_camera.to_ray_cam());

	// Outline
	const float thickness = 5;
	Rectf bounding_box = entity.get_bounding_box();
	DrawRectangleLinesEx(
		Rectangle{
			bounding_box.position.x,
			bounding_box.position.y,
			bounding_box.size.x,
			bounding_box.size.y
		},
		thickness / m_camera.zoom,
		PINK
	);

	EndMode2D();

	// Name
	const int font_size = 20;
	const int width = MeasureText(entity.name.data(), font_size);
	Vec2i text_pos = m_camera.unproject(Vec2f{bounding_box.position.x, bounding_box.position.y + bounding_box.size.y});
	DrawRectangle(text_pos.x, text_pos.y, width, font_size, Color{0, 0, 0, 150});
	DrawText(entity.name.data(), text_pos.x, text_pos.y, font_size, WHITE);
}

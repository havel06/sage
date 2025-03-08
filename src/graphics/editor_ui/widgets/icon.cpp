#include "icon.hpp"
#include "../icon_resource.hpp"
#include "../theme.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"

namespace Editor_UI::Widgets
{

Icon::Icon(const Icon_Resource& res) :
	m_icon_resource{res}
{
}

void Icon::draw(const Theme& theme, float dt)
{
	(void)dt;
	DrawTexturePro(
		m_icon_resource.get(),
		{0, 0, (float)m_icon_resource.get().width, (float)m_icon_resource.get().height},
		{(float)m_position.x, (float)m_position.y, (float)theme.ICON_SIZE, (float)theme.ICON_SIZE},
		{0, 0},
		0,
		Color {
			theme.ON_SURFACE.r,
			theme.ON_SURFACE.g,
			theme.ON_SURFACE.b,
			theme.ON_SURFACE.a,
		}
	);
}

Vec2i Icon::layout(const Theme& theme, Recti bounding_box)
{
	// NOTE - bounding box size is ignored
	m_position = bounding_box.position;
	return {theme.ICON_SIZE, theme.ICON_SIZE};
}

}

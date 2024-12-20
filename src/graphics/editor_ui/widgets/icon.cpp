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

void Icon::draw()
{
	DrawTexturePro(
		m_icon_resource.get(),
		{0, 0, (float)m_icon_resource.get().width, (float)m_icon_resource.get().height},
		{(float)m_position.x, (float)m_position.y, Theme::ICON_SIZE, Theme::ICON_SIZE},
		{0, 0},
		0,
		Color {
			Theme::ON_SURFACE.r,
			Theme::ON_SURFACE.g,
			Theme::ON_SURFACE.b,
			Theme::ON_SURFACE.a,
		}
	);
}

Vec2i Icon::layout(Recti bounding_box)
{
	// NOTE - bounding box size is ignored
	m_position = bounding_box.position;
	return {Theme::ICON_SIZE, Theme::ICON_SIZE};
}

}

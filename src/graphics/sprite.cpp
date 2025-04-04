#include "sprite.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>
#include <assert.h>

Sprite::Sprite(Resource_Handle<Sage_Texture> texture)
{
	m_texture = texture;

	texture_clip.position.x = 0;
	texture_clip.position.y = 0;
	texture_clip.size.x = m_texture.value().get().ray_texture.width;
	texture_clip.size.y = m_texture.value().get().ray_texture.height;
}

bool Sprite::is_null() const
{
	return !m_texture.has_value();
}

void Sprite::draw(Rectf transform, float opacity) const
{
	draw_with_tint(transform, {255, 255, 255, (unsigned char)(opacity * 255)});
}

void Sprite::draw_with_tint(Rectf transform, Colour tint) const
{
	if (!m_texture.has_value())
		return;
	//SG_DEBUG("Sprite texture id: %d", m_texture.id);
	//SG_DEBUG("%d %d", m_texture.width, m_texture.height);

	Rectangle source = {
		(float)texture_clip.position.x,
		(float)texture_clip.position.y,
		(float)texture_clip.size.x,
		(float)texture_clip.size.y,
	};

	Rectangle dest = {
		transform.position.x,
		transform.position.y,
		transform.size.x,
		transform.size.y,
	};

	Color ray_colour = Color{tint.r, tint.g, tint.b, tint.a};
	DrawTexturePro(m_texture.value().get().ray_texture, source, dest, {}, 0, ray_colour);
}

const String& Sprite::get_texture_path() const
{
	assert(m_texture.has_value());
	return m_texture.value().get_path();
}

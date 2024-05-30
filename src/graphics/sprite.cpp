#include "sprite.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>
#include <assert.h>

Sprite::Sprite(const Sage_Texture& texture)
{
	m_texture = texture;

	texture_clip.position.x = 0;
	texture_clip.position.y = 0;
	texture_clip.size.x = texture.ray_texture.width;
	texture_clip.size.y = texture.ray_texture.height;
}

Sprite::Sprite()
{
	m_texture.ray_texture.id = 0;
}

bool Sprite::is_null() const
{
	return m_texture.ray_texture.id <= 0;
}

void Sprite::draw(Rectf transform) const
{
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

	DrawTexturePro(m_texture.ray_texture, source, dest, {}, 0, WHITE);
}

const String& Sprite::get_texture_path() const
{
	return m_texture.path;
}

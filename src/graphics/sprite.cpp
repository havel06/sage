#include "sprite.hpp"
#include "utils/log.hpp"
#include <raylib/raylib.h>
#include <assert.h>

Sprite::Sprite(const Texture& texture)
{
	m_texture = texture;

	texture_clip.position.x = 0;
	texture_clip.position.y = 0;
	texture_clip.size.x = texture.width;
	texture_clip.size.y = texture.height;
}

Sprite::Sprite()
{
	m_texture.id = 0;
}

bool Sprite::is_null() const
{
	return m_texture.id <= 0;
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

	DrawTexturePro(m_texture, source, dest, {}, 0, WHITE);
}

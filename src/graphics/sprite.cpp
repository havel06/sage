#include "sprite.hpp"
#include <raylib/raylib.h>
#include <assert.h>

Sprite::Sprite(const Texture& texture)
{
	m_texture = &texture;

	texture_clip.position.x = 0;
	texture_clip.position.y = 0;
	texture_clip.size.x = texture.width;
	texture_clip.size.y = texture.height;
}

void Sprite::draw(Rectf transform)
{
	assert(m_texture);

	Rectangle source = {
		(float)texture_clip.position.x / m_texture->width,
		(float)texture_clip.position.y / m_texture->height,
		(float)texture_clip.size.x / m_texture->width,
		(float)texture_clip.size.y / m_texture->height,
	};

	Rectangle dest = {
		transform.position.x,
		transform.position.y,
		transform.size.x,
		transform.size.y,
	};

	DrawTexturePro(*m_texture, source, dest, {}, 0, WHITE);
}

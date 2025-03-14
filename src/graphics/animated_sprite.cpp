#include "animated_sprite.hpp"
#include "utils/log.hpp"

Animated_Sprite::Animated_Sprite(const Array<Sprite>& frames, float frame_time)
{
	m_frames = frames;
	m_frame_time = frame_time;
}

Animated_Sprite::Animated_Sprite(const Sprite& sprite)
{
	m_frames.push_back(sprite);
}

void Animated_Sprite::reset_animation()
{
	m_current_frame = 0;
}

void Animated_Sprite::draw(Rectf transform, float time_delta) const
{
	draw_with_tint(transform, time_delta, Colour{255, 255, 255, 255});
}

void Animated_Sprite::draw_with_tint(Rectf transform, float time_delta, Colour tint) const
{
	if (m_frames.empty()) {
		return;
	}

	m_time_since_last_frame += time_delta;

	if (m_time_since_last_frame > m_frame_time) {
		m_time_since_last_frame = 0;
		m_current_frame = (m_current_frame + 1) % m_frames.size();
	}

	m_frames[m_current_frame].draw_with_tint(transform, tint);
}

void Animated_Sprite::draw_with_opacity(Rectf transform, float time_delta, float opacity) const
{
	assert(opacity >= 0);
	assert(opacity <= 1);

	draw_with_tint(transform, time_delta, Colour{255, 255, 255, (unsigned char)(255 * opacity)});
}

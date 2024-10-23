#pragma once

#include "sprite.hpp"
#include "utils/array.hpp"

class Animated_Sprite
{
public:
	Animated_Sprite(const Array<Sprite>& frames, float frame_time);
	Animated_Sprite(const Sprite&);
	Animated_Sprite() = default;
	void draw(Rectf transform, float time_delta) const;
	void draw_with_tint(Rectf transform, float time_delta, Colour tint) const;
	void reset_animation();

	// Getters
	const Sprite& get_current_frame() const { return m_frames[m_current_frame]; }
	const Array<Sprite>& get_frames() const { return m_frames; }
	float get_frame_time() const { return m_frame_time; }

	bool is_null() const { return m_frames.empty(); }
private:
	float m_frame_time = 99999;
	mutable int m_current_frame = 0;
	mutable float m_time_since_last_frame = 0;
	Array<Sprite> m_frames;
};

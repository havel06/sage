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

	// Getters
	const Array<Sprite>& get_frames() const { return m_frames; }
	float get_frame_time() const { return m_frame_time; }
private:
	float m_frame_time = 99999;
	mutable int m_current_frame = 0;
	mutable float m_time_since_last_frame = 0;
	Array<Sprite> m_frames;
};

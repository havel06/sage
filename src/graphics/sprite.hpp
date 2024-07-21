#pragma once

#include "utils/rect.hpp"
#include "utils/string.hpp"
#include "utils/optional.hpp"
#include "texture.hpp"
#include "io/resource/resource_handle.hpp"

class Sprite
{
public:
	Recti texture_clip;

	Sprite(Resource_Handle<Sage_Texture>);
	Sprite() = default;

	void draw(Rectf transform, float opacity = 1) const;
	bool is_null() const;
	const String& get_texture_path() const;
private:
	Optional<Resource_Handle<Sage_Texture>> m_texture;
};

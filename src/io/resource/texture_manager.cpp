#include "texture_manager.hpp"
#include "graphics/texture.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"
#include "utils/profiler.hpp"

Texture_Manager::Texture_Manager(const String& resource_root_path) :
	Resource_Manager(resource_root_path),
	m_fallback_texture{"", create_fallback_texture()}
{
}

Own_Ptr<Resource<Sage_Texture>> Texture_Manager::load_resource(const String& filename)
{
	SG_PROFILE_SCOPE("Texture load");
	Texture texture = LoadTexture(filename.data());

	if (texture.id <= 0) {
		SG_ERROR("Unable to load texture \"%s\".", filename.data());
		return make_own_ptr<Resource<Sage_Texture>>(m_fallback_texture);
	}

	return make_own_ptr<Resource<Sage_Texture>>(filename, Sage_Texture{texture});
}

void Texture_Manager::unload_resource(Sage_Texture& texture, const String&)
{
	UnloadTexture(texture.ray_texture);
}

Sage_Texture Texture_Manager::create_fallback_texture()
{
	Image image = GenImageChecked(2, 2, 1, 1, MAGENTA, BLACK);

	return Sage_Texture {
		LoadTextureFromImage(image)
	};
}

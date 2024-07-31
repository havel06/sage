#include "texture_manager.hpp"
#include "graphics/texture.hpp"
#include "raylib/raylib.h"
#include "utils/log.hpp"
#include "utils/own_ptr.hpp"

Texture_Manager::Texture_Manager(const String& resource_root_path) :
	Resource_Manager(resource_root_path)
{
}

Own_Ptr<Resource<Sage_Texture>> Texture_Manager::load_resource(const String& filename)
{
	Texture texture = LoadTexture(filename.data());

	if (texture.id <= 0) {
		SG_ERROR("Unable to load texture \"%s\".", filename.data());
	}

	return make_own_ptr<Resource<Sage_Texture>>(Sage_Texture{texture, filename});
}

void Texture_Manager::unload_resource(Sage_Texture& texture)
{
	UnloadTexture(texture.ray_texture);
}

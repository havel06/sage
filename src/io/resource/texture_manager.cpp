#include "texture_manager.hpp"
#include "graphics/texture.hpp"
#include "utils/own_ptr.hpp"

Texture_Manager::Texture_Manager(const String& resource_root_path) :
	Resource_Manager(resource_root_path)
{
}

Own_Ptr<Resource<Sage_Texture>> Texture_Manager::load_resource(const String& filename)
{
	return make_own_ptr<Resource<Sage_Texture>>(Sage_Texture{LoadTexture(filename.data()), filename});
}

#include "map_manager.hpp"
#include "../tmj.hpp"
#include "io/resource/resource_system.hpp"
#include "utils/own_ptr.hpp"

Map_Manager::Map_Manager(const String& resource_root_path, Resource_System& res_system) :
	Resource_Manager(resource_root_path),
	m_res_system(res_system)
{
}

Own_Ptr<Map> Map_Manager::load_resource(const String& filename)
{
	TMJ::Map_Loader loader(m_res_system, filename);
	return make_own_ptr<Map>(loader.retrieve_map());
}

#pragma once


// fwd
class Sequence_Loader;
class Texture_Manager;
class Event_Parameter;
namespace JSON {
	class Object_View;
	class Value_View;
}


class Event_Parameter_Parser
{
public:
	Event_Parameter_Parser(Sequence_Loader&, Texture_Manager&);
	void parse(Event_Parameter& parameter, const JSON::Value_View& unresolved_value, const JSON::Object_View& template_parameters);

private:
	// Returns either the value of val, or value of template parameter referred to by val
	JSON::Value_View resolve_value(const JSON::Value_View& val, const JSON::Object_View& template_parameters);

	Sequence_Loader& m_sequence_loader;
	Texture_Manager& m_texture_manager;
};

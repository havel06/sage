#pragma once

// fwd
namespace JSON
{
	class Value_View;
	class Object_View;
}

// Returns either the value of val, or value of template parameter referred to by val
JSON::Value_View resolve_templated_value(const JSON::Value_View& val, const JSON::Object_View& template_parameters);

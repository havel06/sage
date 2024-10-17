#include "template.hpp"
#include "utils/json.hpp"
#include "utils/log.hpp"
#include <string.h>
#include <assert.h>

JSON::Value_View resolve_templated_value(const JSON::Value_View& val, const JSON::Object_View& template_parameters)
{
	if (val.is_string()) {
		const char* str_value = val.as_string("");

		if (strlen(str_value) > 1 && str_value[0] == '$') {
			const char* param_name = str_value + 1;
			if (template_parameters.has(param_name)) {
				return template_parameters.get(param_name);
			} else {
				SG_ERROR("Missing sequence template parameter \"%s\"", param_name);
				assert(false);
			}
		}
	}

	return val;
}

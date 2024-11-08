#include "formatted_text.hpp"

namespace UI
{

String Formatted_Text::to_string() const
{
	String result;

	for (const Formatted_Text_Fragment& fragment : fragments)
		result.append(fragment.text);

	return result;
}

Formatted_Text::Formatted_Text(const String& str)
{
	fragments.push_back(Formatted_Text_Fragment{
		.text = str
	});
}

}

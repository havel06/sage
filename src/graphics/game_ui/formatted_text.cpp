#include "formatted_text.hpp"

namespace Game_UI
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

int Formatted_Text::length() const
{
	int result = 0;

	for (const Formatted_Text_Fragment& fragment : fragments)
		result += fragment.text.length();

	return result;
}

Formatted_Text Formatted_Text::substring(int length) const
{
	Formatted_Text result;

	for (const Formatted_Text_Fragment& fragment : fragments) {
		if (length == 0)
			break;

		else if (length < fragment.text.length()) {
			result.fragments.push_back(Formatted_Text_Fragment{
				.text = fragment.text.substring(0, length),
				.colour = fragment.colour
			});
			break;
		} else {
			result.fragments.push_back(fragment);
			length -= fragment.text.length();
		}
	}

	return result;
}

}

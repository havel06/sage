#pragma once

#include "utils/string.hpp"
#include "utils/colour.hpp"
#include "utils/array.hpp"
#include "utils/optional.hpp"

namespace UI
{

struct Formatted_Text_Fragment
{
	String text;
	Optional<Colour> colour;
};

struct Formatted_Text
{
	Array<Formatted_Text_Fragment> fragments;

	Formatted_Text() = default;
	Formatted_Text(const String&);


	String to_string() const;
};

}

#include "fuzzy_match.hpp"
#include "utils/string.hpp"
#include <ctype.h>

// Whether str[index_str:] is contained in reference[index_ref:]
static bool match_helper(const String& str, const String& reference, int index_str, int index_ref)
{
	if (str.length() <= index_str)
		return true;

	if (reference.length() <= index_ref)
		return false;

	if (str.length() - index_str > reference.length() - index_ref)
		return false;

	if (tolower(str[index_str]) == tolower(reference[index_ref])) {
		return match_helper(str, reference, index_str + 1, index_ref + 1);
	} else {
		return match_helper(str, reference, index_str, index_ref + 1);
	}
}

bool fuzzy_match_string(const String& str, const String& reference)
{
	return match_helper(str, reference, 0, 0);
}

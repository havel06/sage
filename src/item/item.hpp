#pragma once

#include "graphics/sprite.hpp"
#include "utils/string.hpp"
#include "sequence/sequence.hpp"

struct Item
{
	String id;
	String name;
	Sprite sprite;
	Optional<Resource_Handle<Sequence>> assigned_sequence;
};

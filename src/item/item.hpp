#pragma once

#include "graphics/sprite.hpp"
#include "utils/string.hpp"

class Sequence;

struct Item
{
	String id;
	String name;
	Sprite sprite;
	Optional<Resource_Handle<Sequence>> assigned_sequence;
};

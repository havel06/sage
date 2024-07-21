#pragma once

#include "utils/string.hpp"
#include "io/resource/resource_handle.hpp"

class Sequence;

struct Ability
{
	String name;
	Resource_Handle<Sequence> sequence;
};

#pragma once

// fwd
class Sprite;

struct Tile
{
	Sprite* sprite = nullptr;
	bool solid = false;
};

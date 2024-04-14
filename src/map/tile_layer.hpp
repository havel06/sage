#pragma once

#include "utils/array.hpp"
#include "utils/vec2.hpp"
#include "tile.hpp"

class Tile_Layer
{
public:
	Tile_Layer(int width, int height);
	int get_width() const { return m_width; }
	int get_height() const { return m_height; }
	void set_tile(Vec2i position, const Tile&);
	const Tile& get_tile(Vec2i position) const;
	bool is_position_valid(Vec2i) const;
private:
	int m_width;
	int m_height;
	Array<Tile> m_tiles;
};

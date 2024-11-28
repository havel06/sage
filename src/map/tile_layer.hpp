#pragma once

#include "utils/array.hpp"
#include "utils/vec2.hpp"
#include "tile.hpp"

class Tile_Layer
{
public:
	Tile_Layer(int width, int height, const String& name);
	const String& get_name() const { return m_name; }

	int get_width() const { return m_width; }
	int get_height() const { return m_height; }

	void update(float dt); // Call repeatedly

	void set_tile(Vec2i position, const Tile&);
	const Tile& get_tile(Vec2i position) const;
	bool is_position_valid(Vec2i) const;

	float get_opacity() const { return m_opacity; }
	void set_opacity(float value, bool instant = false);
private:
	String m_name;
	int m_width;
	int m_height;
	float m_opacity = 1;
	float m_opacity_target = 1;
	Array<Tile> m_tiles;
};

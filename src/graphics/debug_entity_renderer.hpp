#pragma once

// fwd
class Map_Entities;
class Entity;
class Game_Camera;

class Debug_Entity_Renderer
{
public:
	Debug_Entity_Renderer(const Game_Camera&);
	void draw(const Map_Entities&);
private:
	const Game_Camera& m_camera;
	void draw_entity(const Entity&);
};

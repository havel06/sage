#pragma once

class Party;
class Combat;

class Combat_Renderer
{
public:
	Combat_Renderer(const Party&, const Combat&);
	void draw();

private:
	void draw_party();
	void draw_enemies();

	const Party& m_party;
	const Combat& m_combat;
};

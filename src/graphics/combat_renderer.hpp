#pragma once

class Party;

class Combat_Renderer
{
public:
	Combat_Renderer(const Party&);
	void draw();

private:
	void draw_party();

	const Party& m_party;

};

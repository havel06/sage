#pragma once

// fwd
class Game_Logic_State_Normal;
class Game_Logic_State_Combat;
struct Battle_Description;

enum class Game_Logic_State
{
	normal,
	combat
};

class Game_Logic
{
public:
	Game_Logic(Game_Logic_State_Normal&, Game_Logic_State_Combat&);

	void update(float time_delta);

	Game_Logic_State get_state() const { return m_state; }
	void enter_combat(const Battle_Description&);
	void enter_normal_mode();
private:
	Game_Logic_State m_state = Game_Logic_State::normal;

	Game_Logic_State_Normal& m_state_normal;
	Game_Logic_State_Combat& m_state_combat;
};

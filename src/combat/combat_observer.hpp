#pragma once

class Combat_Observer
{
public:
	virtual void on_battle_begin() = 0;
	virtual void on_hero_ability_selecting_begin() = 0;
	virtual void on_unit_hp_change(int id, int amount) = 0;
};

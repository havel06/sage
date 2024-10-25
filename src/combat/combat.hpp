#pragma once

#include "target_selection_type.hpp"
#include "battle.hpp"

// fwd
class Party;

enum class Combat_Result
{
	won,
	lost,
};

class Combat
{
public:
	Combat(const Party& party);

	const Battle& get_battle() const;
	Battle& get_battle();

	// Observer stuff
	void add_observer(Combat_Observer&);
	void remove_observer(Combat_Observer&);

	// Call every frame
	void update();

	bool is_active() const;
	void start_battle(const Battle_Description&);
private:
	const Party& m_party;

	Array<Combat_Observer*> m_observers;
	Optional<Battle> m_battle;
};

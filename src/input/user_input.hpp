#pragma once

#include "input_event_provider.hpp"

class User_Input : public Input_Event_Provider
{
public:
	void process(Input_Observer&) override;
};

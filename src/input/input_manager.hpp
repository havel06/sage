#pragma once

#include "input_event_provider.hpp"

// FIXME - reconsider name
class Input_Manager : public Input_Event_Provider
{
public:
	void process(Input_Observer&) override;
};

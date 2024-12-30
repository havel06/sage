#pragma once

// fwd
class String;
class Sequence;

class Sequence_Manager_Observer
{
public:
	virtual void on_load(const String& filename, Sequence&) = 0;
	virtual void on_unload(const String& filename, Sequence&) = 0;
};

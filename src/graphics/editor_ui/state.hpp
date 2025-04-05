#pragma once

#include "utils/own_ptr.hpp"
#include "widget_factory.hpp"

namespace Editor_UI
{

// Similar concept to Flutter's State and StatefulWidget.
// A 'State' object is owned by a 'Stateful' widget.
// When the 'State' object needs to be rebuilt, it builds
// a new widget tree representing the widget.

class State
{
public:
	virtual ~State() = default;

	// Build the widget representing the State
	virtual Own_Ptr<Widget_Factory> build(const Theme&) = 0;

	// Needs to be rebuilt.
	// NOTE - A 'Stateful' widget always gets built when added
	// to the widget tree, even if this is set to false, so
	// if the state only needs to get built once, this can be set
	// to false permanently.
	virtual bool is_dirty() const = 0;
};

}

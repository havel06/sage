#pragma once

// fwd
namespace Editor_UI { class Widget; }
template<typename T>
class Own_Ptr;


namespace Editor_UI
{

/*

View_Model allows to store a reference to an object with state in the widget tree.
The View_Model then generates a widget based on its internal state.
To alert the system that the widget needs to be rebuilt, View_Model
needs to return true from is_dirty.
Use along with Widgets::View_Model_Holder.

This pattern is similar to Flutter's `State`.
*/

class View_Model
{
public:
	// Build the widget representing the View_Model
	virtual Own_Ptr<Widget> build() = 0;
	// Needs to be rebuilt
	virtual bool is_dirty() const = 0;
};

}

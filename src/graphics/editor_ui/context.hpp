#pragma once

#include "utils/own_ptr.hpp"
#include "widget_factory.hpp"

namespace Editor_UI
{

class Context
{
public:
	Context(const Theme&);
	Context(Context&&) = default;

	void draw(float dt); // Call each frame
	void input_char(char charater);
	void input_key(int key);
	void set_top_widget(Own_Ptr<Widget_Factory>&&);
private:
	const Theme& m_theme;
	Own_Ptr<Widget> m_top_widget = {};
};

}

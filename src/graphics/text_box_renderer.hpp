#pragma once

#include "ui/widget.hpp"

// fwd
class Text_Box;
class String;
class GUI_Loader;

class Text_Box_Renderer
{
public:
	Text_Box_Renderer(const Text_Box&);
	void draw(float time_delta);
	void load(GUI_Loader&, const String& filename);
private:
	const Text_Box& m_text_box;
	UI::Widget_Ptr m_widget;
};

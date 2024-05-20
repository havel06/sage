#pragma once

#include "ui/widget.hpp"

class Text_Box;
class String;

class Text_Box_Renderer
{
public:
	Text_Box_Renderer(const Text_Box&);
	void draw();
	void load(const String& project_root);
private:
	const Text_Box& m_text_box;
	UI::Widget_Ptr m_widget;
};

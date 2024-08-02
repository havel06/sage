#pragma once

namespace UI
{

class Box;
class Button;
class Image;
class Text;

class Widget_Visitor
{
public:
	virtual void visit_box(Box& box) = 0;
	virtual void visit_button(Button& text) = 0;
	virtual void visit_image(Image& image) = 0;
	virtual void visit_text(Text& text) = 0;
};

}

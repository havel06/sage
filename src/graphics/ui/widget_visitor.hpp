#pragma once

#include "utils/concepts.hpp"

namespace UI
{

class Box;
class Button;
class Image;
class Text;
class Widget;

class Widget_Visitor
{
public:
	virtual void visit_box(Box& box) = 0;
	virtual void visit_button(Button& text) = 0;
	virtual void visit_image(Image& image) = 0;
	virtual void visit_text(Text& text) = 0;
};


// A visitor that provides default behavior for all visit functions
class Defaulted_Widget_Visitor : public Widget_Visitor
{
	void visit_box(Box&) override {}
	void visit_button(Button&) override {}
	void visit_image(Image&) override {}
	void visit_text(Text&) override {}
};


// A visitor that only visits text elements using a generic callable
template<typename Fn>
requires Concepts::Callable<Fn, Text&>
class Text_Widget_Visitor : public Defaulted_Widget_Visitor
{
public:
	Text_Widget_Visitor(Fn fn) : m_fn{fn} {}
private:
	void visit_text(Text& text) override { m_fn(text); }
	Fn m_fn; // Store the lambda here to prevent dangling pointer
};


// A visitor that only visits image elements using a generic callable
template<typename Fn>
requires Concepts::Callable<Fn, Image&>
class Image_Widget_Visitor : public Defaulted_Widget_Visitor
{
public:
	Image_Widget_Visitor(Fn fn) : m_fn{fn} {}
private:
	void visit_image(Image& image) override { m_fn(image); }
	Fn m_fn; // Store the lambda here to prevent dangling pointer
};


// A visitor that only visits button elements using a generic callable
template<typename Fn>
requires Concepts::Callable<Fn, Button&>
class Button_Widget_Visitor : public Defaulted_Widget_Visitor
{
public:
	Button_Widget_Visitor(Fn fn) : m_fn{fn} {}
private:
	void visit_button(Button& button) override { m_fn(button); }
	Fn m_fn; // Store the lambda here to prevent dangling pointer
};


}

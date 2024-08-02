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

	template<typename Fn>
	requires Concepts::Callable<Fn, Text&>
	static auto create_text_visitor(Fn fn);
};


// Implemantation

template<typename Fn>
requires Concepts::Callable<Fn, Text&>
auto Widget_Visitor::create_text_visitor(Fn fn)
{
	class Derived_Visitor : public Widget_Visitor
	{
	public:
		Derived_Visitor(Fn fn_) :
			m_fn{fn_}
		{
		}

	private:

		virtual void visit_box(Box&) override {}
		virtual void visit_button(Button&) override {}
		virtual void visit_image(Image&) override {}
		virtual void visit_text(Text& text) override
		{
			m_fn(text);
		}

		Fn m_fn; // Store the lambda here to prevent dangling pointer
	};

	return Derived_Visitor{fn};
}

}

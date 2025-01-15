#pragma once

#include "../widget.hpp"
#include "../theme.hpp"
#include "utils/string.hpp"
#include "utils/colour.hpp"
#include "utils/own_ptr.hpp"

// fwd
struct Font;

namespace Editor_UI::Widgets
{

class Input_Constraint
{
public:
	virtual bool is_valid(const String&) const = 0;
	virtual ~Input_Constraint() = default;
};

class Input_Constraint_None : public Input_Constraint
{
	bool is_valid(const String&) const override { return true; }
};

class Input_Constraint_Integer : public Input_Constraint
{
	bool is_valid(const String&) const override;
};

// Integer or decimal
class Input_Constraint_Number : public Input_Constraint
{
	bool is_valid(const String&) const override;
};

class Input : public Widget
{
public:
	bool active = false;
	Colour background = Theme::SURFACE;

	Input(const Font& font, const String& label, Own_Ptr<Input_Constraint>&&);
	const String& get_content() { return m_content; }
	bool is_valid() const;

	void draw(float dt) override;
	Vec2i layout(Recti bounding_box) override;
	void set_content(const String&);
	void handle_mouse(Vec2i position, bool click) override;
	void handle_character(char) override;
	void handle_key(int key) override;
private:
	const Font& m_font;
	Own_Ptr<Input_Constraint> m_constraint;
	String m_label;
	String m_content;
	Recti m_bounding_box;
	float m_time_since_cursor_blink = 0;
};

}

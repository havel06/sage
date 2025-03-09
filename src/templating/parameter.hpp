#pragma once

#include "graphics/animated_sprite.hpp"
#include "graphics/game_ui/formatted_text.hpp"
#include "utils/string.hpp"
#include "utils/direction.hpp"
#include "combat/target_selection_type.hpp"
#include "sequence/condition.hpp"
#include "combat/battle_desc.hpp"
#include "map/position.hpp"

// fwd
class Int_Parameter;
class Float_Parameter;
class String_Parameter;
class Direction_Parameter;
class Sprite_Parameter;
class String_Array_Parameter;
class Target_Selection_Type_Parameter;
class Condition_Parameter;
class Condition_Array_Parameter;
class Battle_Units_Layout_Parameter;
class Formatted_Text_Parameter;
class Position_Parameter;

// Visitor pattern for parameters

class Parameter_Visitor
{
public:
	virtual void visit(Int_Parameter&) = 0;
	virtual void visit(Float_Parameter&) = 0;
	virtual void visit(String_Parameter&) = 0;
	virtual void visit(Direction_Parameter&) = 0;
	virtual void visit(Sprite_Parameter&) = 0;
	virtual void visit(String_Array_Parameter&) = 0;
	virtual void visit(Target_Selection_Type_Parameter&) = 0;
	virtual void visit(Condition_Parameter&) = 0;
	virtual void visit(Condition_Array_Parameter&) = 0;
	virtual void visit(Battle_Units_Layout_Parameter&) = 0;
	virtual void visit(Formatted_Text_Parameter&) = 0;
	virtual void visit(Position_Parameter&) = 0;
};

// Abstract parameter class

class Parameter
{
public:
	virtual void accept_visitor(Parameter_Visitor&) = 0;

	bool is_templated() const { return m_template_parameter_name.has_value(); }

	const String& get_template_paramter_name()
	{
		assert(m_template_parameter_name.has_value());
		return m_template_parameter_name.value();
	}

	void set_template_parameter_name(const String& name) { m_template_parameter_name = name; }

private:
	Optional<String> m_template_parameter_name; // If this parameter is templated, this is where the parameter name is stored.
};


// Derived classes

class Int_Parameter final : public Parameter
{
public:
	int value = 0;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Float_Parameter final : public Parameter
{
public:
	float value = 0;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class String_Parameter final : public Parameter
{
public:
	String value = {};
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Direction_Parameter final : public Parameter
{
public:
	Direction value = {};
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Sprite_Parameter final : public Parameter
{
public:
	Animated_Sprite value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

// TODO - more generic array parameters?
class String_Array_Parameter final : public Parameter
{
public:
	Array<String> value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Target_Selection_Type_Parameter final : public Parameter
{
public:
	Target_Selection_Type value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Condition_Parameter final : public Parameter
{
public:
	Own_Ptr<Condition> value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Condition_Array_Parameter final : public Parameter
{
public:
	Array<Own_Ptr<Condition>> value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Battle_Units_Layout_Parameter final : public Parameter
{
public:
	Battle_Units_Layout value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Formatted_Text_Parameter final : public Parameter
{
public:
	Game_UI::Formatted_Text value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Position_Parameter final : public Parameter
{
public:
	Position value;
	void accept_visitor(Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

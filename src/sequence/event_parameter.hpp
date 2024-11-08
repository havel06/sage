#pragma once

#include "graphics/animated_sprite.hpp"
#include "graphics/ui/formatted_text.hpp"
#include "utils/string.hpp"
#include "utils/direction.hpp"
#include "combat/target_selection_type.hpp"
#include "sequence/condition.hpp"
#include "combat/battle_desc.hpp"

// fwd
class Int_Event_Parameter;
class Float_Event_Parameter;
class String_Event_Parameter;
class Direction_Event_Parameter;
class Sprite_Event_Parameter;
class String_Array_Event_Parameter;
class Target_Selection_Type_Event_Parameter;
class Condition_Event_Parameter;
class Battle_Units_Layout_Event_Parameter;
class Formatted_Text_Event_Parameter;

// Visitor pattern for parameters

class Event_Parameter_Visitor
{
public:
	virtual void visit(Int_Event_Parameter&) = 0;
	virtual void visit(Float_Event_Parameter&) = 0;
	virtual void visit(String_Event_Parameter&) = 0;
	virtual void visit(Direction_Event_Parameter&) = 0;
	virtual void visit(Sprite_Event_Parameter&) = 0;
	virtual void visit(String_Array_Event_Parameter&) = 0;
	virtual void visit(Target_Selection_Type_Event_Parameter&) = 0;
	virtual void visit(Condition_Event_Parameter&) = 0;
	virtual void visit(Battle_Units_Layout_Event_Parameter&) = 0;
	virtual void visit(Formatted_Text_Event_Parameter&) = 0;
};

// Abstract parameter class

class Event_Parameter
{
public:
	virtual void accept_visitor(Event_Parameter_Visitor&) = 0;
};


// Derived classes

class Int_Event_Parameter final : public Event_Parameter
{
public:
	int value = 0;
	void accept_visitor(Event_Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Float_Event_Parameter final : public Event_Parameter
{
public:
	float value = 0;
	void accept_visitor(Event_Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class String_Event_Parameter final : public Event_Parameter
{
public:
	String value = {};
	void accept_visitor(Event_Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Direction_Event_Parameter final : public Event_Parameter
{
public:
	Direction value = {};
	void accept_visitor(Event_Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Sprite_Event_Parameter final : public Event_Parameter
{
public:
	Animated_Sprite value;
	void accept_visitor(Event_Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

// TODO - more generic array parameters?
class String_Array_Event_Parameter final : public Event_Parameter
{
public:
	Array<String> value;
	void accept_visitor(Event_Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Target_Selection_Type_Event_Parameter final : public Event_Parameter
{
public:
	Target_Selection_Type value;
	void accept_visitor(Event_Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Condition_Event_Parameter final : public Event_Parameter
{
public:
	Own_Ptr<Condition> value;
	void accept_visitor(Event_Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Battle_Units_Layout_Event_Parameter final : public Event_Parameter
{
public:
	Battle_Units_Layout value;
	void accept_visitor(Event_Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

class Formatted_Text_Event_Parameter final : public Event_Parameter
{
public:
	UI::Formatted_Text value;
	void accept_visitor(Event_Parameter_Visitor& visitor) override { visitor.visit(*this); }
};

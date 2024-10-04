#pragma once

#include <raylib/raylib.h>
#include "utils/colour.hpp"

class Sage_Shader
{
public:
	Sage_Shader();
	~Sage_Shader();
	void begin();
	void end();
	void set_highlight(Colour colour);
private:
	Shader m_shader;
};

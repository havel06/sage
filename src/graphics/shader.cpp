#include "shader.hpp"
#include "raylib/raylib.h"

Sage_Shader::Sage_Shader()
{
	const char* code = R"(
#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec4 highlight;

out vec4 finalColor;

void main()
{
	// Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);

    finalColor = vec4(mix((texelColor*colDiffuse).rgb, highlight.rgb, highlight.w), texelColor.a);
}
	)";

	m_shader = LoadShaderFromMemory(0, code);
}

Sage_Shader::~Sage_Shader()
{
	UnloadShader(m_shader);
}

void Sage_Shader::begin()
{
	BeginShaderMode(m_shader);
}

void Sage_Shader::end()
{
	EndShaderMode();
}

void Sage_Shader::set_highlight(Colour colour)
{
	float vec4[4] = {
		(float)colour.r / 255,
		(float)colour.g / 255,
		(float)colour.b / 255,
		(float)colour.a / 255
	};

	SetShaderValue(m_shader, GetShaderLocation(m_shader, "highlight"), vec4, SHADER_UNIFORM_VEC4);
}

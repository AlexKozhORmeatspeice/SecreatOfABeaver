#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

out vec2 v_TexCoords;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * position;
   v_TexCoords = texCoords;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	float radius = 0.5f;
	vec4 texColor = 2*u_Color + 1;

	color = u_Color;
};
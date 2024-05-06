#shader vertex
#version 330 core
layout(location = 0) in vec4 a_vPosition;
layout(location = 1) in vec2 a_localPos;

out vec2 localPos;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * a_vPosition;
   localPos = a_localPos;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 o_color;

in vec2 localPos;
uniform vec4 u_Color;

void main() 
{
	vec2 uv = localPos * 2.0 - 1.0;
	float fade = 0.01;
	float thickness = 0.03;

	float dist = 1.0 - length(uv);
	vec3 color = vec3(smoothstep(0.0, fade, dist));

	color *= vec3(smoothstep(thickness + fade, thickness, dist));

	if(color == vec3(0.0, 0.0, 0.0))
		discard;

	o_color = vec4(u_Color.rgb * color, 1.0);

};
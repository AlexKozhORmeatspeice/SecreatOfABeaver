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

uniform sampler2D u_Texture;

uniform float now;
uniform float max;

uniform vec4 u_FirstColor;


void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoords);

	float fade = (now / max);
	float thick = 0.1;
	float tonColor = smoothstep(fade - thick, fade + thick, v_TexCoords.x);
	
	vec4 baseColor = vec4(u_FirstColor.r * tonColor, u_FirstColor.g * (1.0 - tonColor), u_FirstColor.b, 1.0);
	
	if(texColor.a == 0.0)
		discard;


	if(texColor.rgb == vec3(0.0, 0.0, 0.0))
	{
		color = texColor;
	}
	else
	{
		color = baseColor * texColor;
	}
};
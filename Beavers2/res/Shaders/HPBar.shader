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

uniform float nowHP;
uniform float maxHP;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoords);

	float fade = (nowHP / maxHP);
	float thick = 0.1;
	float tonColor = smoothstep(fade - thick, fade + thick, v_TexCoords.x);
	
	vec4 baseColor = vec4(tonColor, 1.0 - tonColor, 0.0, 1.0);
	color = baseColor;
	
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
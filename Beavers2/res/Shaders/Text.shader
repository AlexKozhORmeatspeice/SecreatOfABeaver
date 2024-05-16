#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

out vec2 v_TexCoords;

uniform mat4 u_MVP;
uniform mat4 u_SCALE_AND_TRANSLATE;
void main()
{
   gl_Position = u_MVP * position;
   vec4 tex_coords4 = vec4(texCoords.x, texCoords.y, 0.0, 1.0); 
   v_TexCoords = (u_SCALE_AND_TRANSLATE * tex_coords4).xy;
};
#shader fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoords);

	if(length(texColor.rgb) < 0.02)
		discard;

	color = texColor * u_Color;
};
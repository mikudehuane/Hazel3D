#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform float u_MixValue = 0.2;

void main()
{
	color = mix(texture(u_Texture1, v_TexCoord), texture(u_Texture2, v_TexCoord), u_MixValue);
}

#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color = vec4(1.0);
uniform float u_ColorMixAlpha = 0.0;

void main()
{
	color = mix(texture(u_Texture, v_TexCoord), u_Color, u_ColorMixAlpha);
}

#version 330 core

layout(location = 0) out vec4 color;

struct Light
{
	vec3 color;
};

uniform Light u_Light;

void main()
{
	color = vec4(u_Light.color, 1.0);
	color = vec4(1.0);
}

#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform mat3 u_TransformNormal;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPosition;

void main()
{
	v_TexCoord = a_TexCoord;
	v_Normal = u_TransformNormal * a_Normal;
	vec4 worldCoord = u_Transform * vec4(a_Position, 1.0f);
	v_FragPosition = worldCoord.xyz;
	gl_Position = u_ViewProjection * worldCoord;
}

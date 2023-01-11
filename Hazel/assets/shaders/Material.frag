#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPosition;

// scene globals
// light
uniform vec3 u_LightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 u_LightPosition;
uniform float u_LightAmbientIntensity = 0.1;
uniform float u_LightDiffuseIntensity = 1.0;
uniform float u_LightSpecularIntensity = 0.5;
// camera
uniform vec3 u_ViewPosition;

// object attributes
uniform sampler2D u_Texture;
uniform vec4 u_Color = vec4(1.0);
uniform float u_ColorMixAlpha = 0.0;

void main()
{
	vec4 objectColor = mix(texture(u_Texture, v_TexCoord), u_Color, u_ColorMixAlpha);

	// ambient
	vec3 ambient = u_LightAmbientIntensity * u_LightColor;

	// diffuse
	vec3 normal = normalize(v_Normal);
	vec3 lightDir = normalize(u_LightPosition - v_FragPosition);
	float diffuseIntensity = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diffuseIntensity * u_LightDiffuseIntensity * u_LightColor;

	// specular
	vec3 viewDir = normalize(u_ViewPosition - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularIntensity = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularIntensity * u_LightSpecularIntensity * u_LightColor;

	color = vec4(objectColor.rgb * (ambient + diffuse + specular), objectColor.a);
}

#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPosition;

// scene globals
// light
struct Light
{
	vec4 position;
	vec3 color;
	float ambient;
	float diffuse;
	float specular;
};
uniform Light u_Light;
// camera
uniform vec3 u_ViewPosition;

// object attributes
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
uniform Material u_Material;

void main()
{
	vec4 diffuseColor = texture(u_Material.diffuse, v_TexCoord);
	
	// ambient
	vec3 ambient = u_Light.ambient * u_Light.color * diffuseColor.rgb;

	// diffuse
	vec3 normal = normalize(v_Normal);
	// TODO(islander): separete shaders to avoid branching
	vec3 lightDir;
	if (u_Light.position.w == 0.0)
	{
		lightDir = normalize(-u_Light.position.xyz);
	}
	else if (u_Light.position.w == 1.0)
	{
		lightDir = normalize(u_Light.position.xyz - v_FragPosition);
	}
	else
	{
		// TODO(islander): error
		lightDir = vec3(0.0);  
	}
	float diffuseIntensity = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = u_Light.diffuse * u_Light.color * diffuseIntensity * diffuseColor.rgb;

	// specular
	vec3 viewDir = normalize(u_ViewPosition - v_FragPosition);
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularIntensity = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = (
		u_Light.specular * u_Light.color * specularIntensity 
		* texture(u_Material.specular, v_TexCoord).rgb
	);
	
	// emission
	vec3 emission = texture(u_Material.emission, v_TexCoord).rgb;

	color = vec4(ambient + diffuse + specular + emission, 1.0);
	// clip to 1.0
	color = min(color, vec4(1.0));
}

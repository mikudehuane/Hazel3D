#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPosition;

uniform vec3 u_ViewPosition;

struct DirectionalLight
{
	vec3 direction;  // from light to object, normalized
	vec3 color;

	float ambient;
	float diffuse;
	float specular;
};
uniform DirectionalLight u_DirectionalLight;

struct PointLight
{
	vec3 position;
	vec3 color;

    float ambient;
    float diffuse;
    float specular;

    float constant;
    float linear;
    float quadratic;
};
// TODO(islander): maybe change this in C++ program
#define MAX_POINT_LIGHT 4
uniform int u_PointLightCount = 0;
uniform PointLight u_PointLights[MAX_POINT_LIGHT];

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 color;

    float ambient;
    float diffuse;
    float specular;

    float constant;
    float linear;
    float quadratic;

	float cutOff;
	float outerCutOff;
};
uniform int u_SpotLightCount = 0;  
uniform SpotLight u_SpotLight;  // TODO(islander): should be array 

// object attributes
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
uniform Material u_Material;

// global variables
vec4 diffuseColor = texture(u_Material.diffuse, v_TexCoord);
vec4 reflectColor = texture(u_Material.specular, v_TexCoord);
vec3 normal = normalize(v_Normal);  // linear interpolation may change the length, so normalization is needed?
vec3 viewDir = normalize(u_ViewPosition - v_FragPosition);

vec3 CalcDirectionalLight(DirectionalLight light)
{
	// TODO(islander): optimize out the normalize
	vec3 lightDir = normalize(-light.direction);
	
	// ambient
	vec3 ambient = light.ambient * light.color * diffuseColor.rgb;
	
	// diffuse
	float diffuseIntensity = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * light.color * diffuseIntensity * diffuseColor.rgb;

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularIntensity = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = light.specular * light.color * specularIntensity * reflectColor.rgb;

	return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light)
{
	vec3 lightDir = normalize(light.position.xyz - v_FragPosition);

	float dist= length(light.position.xyz - v_FragPosition);
	float attenuation = 1.0 / (
		light.constant + light.linear * dist +  light.quadratic * (dist * dist)
	);

	// ambient
	vec3 ambient = light.ambient * light.color * diffuseColor.rgb;
	
	// diffuse
	float diffuseIntensity = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * light.color * diffuseIntensity * diffuseColor.rgb;

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularIntensity = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = light.specular * light.color * specularIntensity * reflectColor.rgb;

	return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight light)
{
	vec3 lightDir = normalize(light.position.xyz - v_FragPosition);

	float dist= length(light.position.xyz - v_FragPosition);
	float attenuation = 1.0 / (
		light.constant + light.linear * dist +  light.quadratic * (dist * dist)
	);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// ambient
	vec3 ambient = light.ambient * light.color * diffuseColor.rgb;
	
	// diffuse
	float diffuseIntensity = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * light.color * diffuseIntensity * diffuseColor.rgb;

	// specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularIntensity = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = light.specular * light.color * specularIntensity * reflectColor.rgb;

	return (ambient + diffuse + specular) * attenuation * intensity;
}

void main()
{
	color = vec4(0.0, 0.0, 0.0, 1.0);  // result buffer

	vec3 directionalColor = CalcDirectionalLight(u_DirectionalLight);
	color.rgb += directionalColor;

	for(int i = 0; i < min(u_PointLightCount, MAX_POINT_LIGHT); i++)
	{
        color.rgb += CalcPointLight(u_PointLights[i]);
	}

	// TODO(islander): temporarily only one spot light
	for(int i = 0; i < u_SpotLightCount; ++i)
	{
		color.rgb += CalcSpotLight(u_SpotLight);
	}	

	// emission
	vec3 emission = texture(u_Material.emission, v_TexCoord).rgb;
	color.rgb += emission;
	
	// clip to 1.0
	color = min(color, vec4(1.0));
}

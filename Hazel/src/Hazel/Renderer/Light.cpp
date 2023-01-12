#include "hzpch.h"
#include "Light.h"

namespace Hazel {

	Ref<Light> Light::Create(
		const glm::vec3& color, const glm::vec3& position,
		float ambientIntensity, float diffuseIntensity, float specularIntensity,
		LightType type
	)
	{
		return CreateRef<Light>(color, position, ambientIntensity, diffuseIntensity, specularIntensity, type);
	}

	Light::Light(const glm::vec3& color, const glm::vec3& position, float ambientIntensity, float diffuseIntensity, float specularIntensity, LightType type)
		:
		m_Color(color), m_Position(position, -1.0f),
		m_AmbientIntensity(ambientIntensity), m_DiffuseIntensity(diffuseIntensity), m_SpecularIntensity(specularIntensity)
	{
		SetType(type);  // m_Position.w is changed properly
	}

	inline void Light::SetType(LightType type)
	{
		m_Type = type;
		float lightW = 0.0f;
		switch (m_Type)
		{
		case Directional: lightW = 0.0f; break;
		case Point: lightW = 1.0f; break;
		default: HZ_CORE_ASSERT(false, "Unknown light type!");
		}
		m_Position.w = lightW;
	}

}


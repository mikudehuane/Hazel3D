#include "hzpch.h"
#include "Light.h"

namespace Hazel {
	Ref<Light> Light::Create(
		const glm::vec3& color, const glm::vec3& position,
		float ambientIntensity, float diffuseIntensity, float specularIntensity)
	{
		return CreateRef<Light>(color, position, ambientIntensity, diffuseIntensity, specularIntensity);
	}
}


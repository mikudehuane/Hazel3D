#include "hzpch.h"
#include "Light.h"

namespace Hazel {
	Ref<Light> Light::Create(const glm::vec3& color, const glm::vec3& position)
	{
		return CreateRef<Light>(color, position);
	}
}


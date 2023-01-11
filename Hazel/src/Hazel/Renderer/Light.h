#pragma once

#include <glm/glm.hpp>

#include "Hazel/Core/Core.h"

namespace Hazel {
	
	class Light
	{
	public:
		static Ref<Light> Create(const glm::vec3& color, const glm::vec3& position = glm::vec3(0.0f));
	public:
		Light(const glm::vec3& color, const glm::vec3& position = glm::vec3(0.0f))
			: m_Color(color), m_Position(position)
		{
		}

		virtual ~Light() = default;

		//virtual void Bind(const Ref<Shader>& shader, uint32_t lightIndex) = 0;

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetColor() const { return m_Color; }

		inline void SetPosition(const glm::vec3& position) { m_Position = position; }
		inline void SetColor(const glm::vec3& color) { m_Color = color; }
	private:
		glm::vec3 m_Color;
		glm::vec3 m_Position;
	};

}

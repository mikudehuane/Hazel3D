#pragma once

#include <glm/glm.hpp>

#include "Hazel/Core/Core.h"

namespace Hazel {
	
	class Light
	{
	public:
		enum LightType {
			Directional = 0,
			Point = 1,
			Spot = 2
		};
	public:
		static Ref<Light> Create(
			const glm::vec3& color, const glm::vec3& position = glm::vec3(0.0f),
			float ambientIntensity = 0.1f, float diffuseIntensity = 1.0f, float specularIntensity = 1.0f,
			LightType type = Directional
		);
	public:
		Light(
			const glm::vec3& color, const glm::vec3& position,
			float ambientIntensity, float diffuseIntensity, float specularIntensity,
			LightType type
		);

		virtual ~Light() = default;

		//virtual void Bind(const Ref<Shader>& shader, uint32_t lightIndex) = 0;

		inline const glm::vec4& GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& position) 
		{ 
			m_Position = glm::vec4(position, m_Position.w); 
		}

		inline const glm::vec3& GetColor() const { return m_Color; }
		inline void SetColor(const glm::vec3& color) { m_Color = color; }

		inline LightType GetType() const { return m_Type; }
		inline void SetType(LightType type);

		inline float GetAmbientIntensity() const { return m_AmbientIntensity; }
		inline void SetAmbientIntensity(float ambientIntensity) { m_AmbientIntensity = ambientIntensity; }
		inline float GetDiffuseIntensity() const { return m_DiffuseIntensity; }
		inline void SetDiffuseIntensity(float diffuseIntensity) { m_DiffuseIntensity = diffuseIntensity; }
		inline float GetSpecularIntensity() const { return m_SpecularIntensity; }
		inline void SetSpecularIntensity(float specularIntensity) { m_SpecularIntensity = specularIntensity; }
		inline void SetIntensity(float ambientIntensity, float diffuseIntensity, float specularIntensity)
		{
			m_AmbientIntensity = ambientIntensity;
			m_DiffuseIntensity = diffuseIntensity;
			m_SpecularIntensity = specularIntensity;
		}

	private:
		LightType m_Type;
		glm::vec3 m_Color;
		glm::vec4 m_Position;  // w = 0 for parallel 1 for point
		float m_AmbientIntensity, m_DiffuseIntensity, m_SpecularIntensity;
	};

}

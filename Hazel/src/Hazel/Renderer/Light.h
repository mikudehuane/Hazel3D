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
		Light(
			const glm::vec3& color, const glm::vec4& position,
			float ambientIntensity, float diffuseIntensity, float specularIntensity,
			LightType type
		) :
			m_Color(color), m_Type(type), m_Position(position),
			m_AmbientIntensity(ambientIntensity), m_DiffuseIntensity(diffuseIntensity), m_SpecularIntensity(specularIntensity)
		{}

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
		float m_AmbientIntensity, m_DiffuseIntensity, m_SpecularIntensity;
		glm::vec4 m_Position;  // w = 0.0f means directional light
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(
			const glm::vec3& color, const glm::vec3& direction,
			float ambientIntensity = 0.1f, float diffuseIntensity = 1.0f, float specularIntensity = 1.0f
		): 
			Light(color, {direction, 0.0f}, ambientIntensity, diffuseIntensity, specularIntensity, Directional)
		{
		}
	};
}

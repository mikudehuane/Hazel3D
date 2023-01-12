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

	class PointLight : public Light
	{
	public:
		// illumination range = 50 By default
		PointLight(
			const glm::vec3& color, const glm::vec3& position,
			float ambientIntensity = 0.1f, float diffuseIntensity = 1.0f, float specularIntensity = 1.0f,
			float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f
		) :
			Light(color, { position, 1.0f }, ambientIntensity, diffuseIntensity, specularIntensity, Point),
			m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic)
		{
		}

		inline float GetConstant() const { return m_Constant; }
		inline void SetConstant(float constant) { m_Constant = constant; }
		inline float GetLinear() const { return m_Linear; }
		inline void SetLinear(float linear) { m_Linear = linear; }
		inline float GetQuadratic() const { return m_Quadratic; }
		inline void SetQuadratic(float quadratic) { m_Quadratic = quadratic; }
		inline void SetAttenuation(float constant, float linear, float quadratic)
		{
			m_Constant = constant;
			m_Linear = linear;
			m_Quadratic = quadratic;
		}
	private:
		float m_Constant, m_Linear, m_Quadratic;
	};

	class SpotLight : public Light
	{
	public:
		SpotLight(
			const glm::vec3& color, const glm::vec3& position, const glm::vec3& direction,
			float ambientIntensity = 0.1f, float diffuseIntensity = 1.0f, float specularIntensity = 1.0f,
			float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f,
			float cutOff = glm::cos(glm::radians(12.5f)), float outerCutOff = glm::cos(glm::radians(17.5f))
		) :
			Light(color, { position, 1.0f }, ambientIntensity, diffuseIntensity, specularIntensity, Spot),
			m_Direction(direction), m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic),
			m_CutOff(cutOff), m_OuterCutOff(outerCutOff)
		{
		}

		inline const glm::vec3& GetDirection() const { return m_Direction; }
		inline void SetDirection(const glm::vec3& direction) { m_Direction = direction; }

		inline float GetConstant() const { return m_Constant; }
		inline void SetConstant(float constant) { m_Constant = constant; }
		inline float GetLinear() const { return m_Linear; }
		inline void SetLinear(float linear) { m_Linear = linear; }
		inline float GetQuadratic() const { return m_Quadratic; }
		inline void SetQuadratic(float quadratic) { m_Quadratic = quadratic; }
		inline void SetAttenuation(float constant, float linear, float quadratic)
		{
			m_Constant = constant;
			m_Linear = linear;
			m_Quadratic = quadratic;
		}

		inline float GetCutOff() const { return m_CutOff; }
		inline void SetCutOff(float cutOff) { m_CutOff = cutOff; }
		inline float GetOuterCutOff() const { return m_OuterCutOff; }
		inline void SetOuterCutOff(float outerCutOff) { m_OuterCutOff = outerCutOff; }
		inline void SetCutOffs(float cutOff, float outerCutOff)
		{
			m_CutOff = cutOff;
			m_OuterCutOff = outerCutOff;
		}
	private:
		float m_CutOff, m_OuterCutOff;
		float m_Constant, m_Linear, m_Quadratic;
		glm::vec3 m_Direction;
	};
}

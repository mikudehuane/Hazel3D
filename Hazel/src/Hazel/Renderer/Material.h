#pragma once

#include "Hazel/Core/Core.h"
#include <Hazel/Renderer/Texture.h>
#include <Hazel/Renderer/Shader.h>

#include <glm/glm.hpp>

namespace Hazel {

	class Material
	{
	public:
		Material(Ref<Shader> shader, float shininess = 32.0f);
		
		void SetDiffuseMap(Ref<Texture2D> texture);
		void SetSpecularMap(Ref<Texture2D> texture);
		void SetEmissionMap(Ref<Texture2D> texture);

		inline float GetShininess() const { return m_Shininess; }
		inline void SetShininess(float shininess) { m_Shininess = shininess; }

		inline const Ref<Shader>& GetShader() const { return m_Shader; }

		void Bind();
	private:
		static const int s_DiffuseSlot = 0;
		static const int s_SpecularSlot = 1;
		static const int s_EmissionSlot = 2;
	private:
		Ref<Shader> m_Shader;
		Ref<Texture2D> m_DiffuseMap;
		Ref<Texture2D> m_SpecularMap;
		Ref<Texture2D> m_EmissionMap;
		float m_Shininess;
	};

}

#pragma once

#include "Hazel/Core/Core.h"
#include <Hazel/Renderer/Texture.h>
#include <Hazel/Renderer/Shader.h>

#include <glm/glm.hpp>

namespace Hazel {

	class Material
	{
	public:
		Material(Ref<Shader> shader);
		void SetTexture(Ref<Texture2D> texture);
		// add color as mixed, mix with factor mixAlpha
		void SetColor(const glm::vec4& color, float mixAlpha = 1.0f);

		inline const Ref<Shader>& GetShader() const { return m_Shader; }

		void Bind();
	private:
		static const int s_TextureSlot = 0;
		Ref<Shader> m_Shader;
		Ref<Texture2D> m_Texture2D;
		float m_ColorMixAlpha = 0.0f;
		glm::vec4 m_Color = glm::vec4(1.0f);
	};

}

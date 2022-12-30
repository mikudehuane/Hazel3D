#include "hzpch.h"
#include "Material.h"
#include "Renderer.h"

namespace Hazel {

	Material::Material(Ref<Shader> shader)
		: m_Shader(shader), m_Texture2D(Renderer::GetWhiteTexture2D())
	{
	}

	void Material::SetTexture(Ref<Texture2D> texture)
	{
		m_Texture2D = texture;
	}

	void Material::SetColor(const glm::vec4& color, float mixAlpha)
	{
		m_Color = color;
		m_ColorMixAlpha = mixAlpha;
	}

	void Material::Bind()
	{
		m_Shader->Bind();
		m_Shader->SetInt("u_Texture", s_TextureSlot);
		m_Shader->SetFloat4("u_Color", m_Color);
		m_Shader->SetFloat("u_ColorMixAlpha", m_ColorMixAlpha);

		m_Texture2D->Bind(s_TextureSlot);
	}

}


#include "hzpch.h"
#include "Material.h"
#include "Renderer.h"

namespace Hazel {

	Material::Material(Ref<Shader> shader)
		: m_Shader(shader)
	{
	}

	void Material::SetTexture(Ref<Texture2D> texture)
	{
		m_Texture2D = texture;
	}

	void Material::Bind()
	{
		m_Shader->Bind();
		m_Shader->SetInt("u_Texture", s_TextureSlot);

		m_Texture2D->Bind(s_TextureSlot);
	}

}


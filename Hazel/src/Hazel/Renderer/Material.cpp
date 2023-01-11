#include "hzpch.h"
#include "Material.h"
#include "Renderer.h"

namespace Hazel {

	Material::Material(Ref<Shader> shader, float shininess)
		: m_Shader(shader), m_Shininess(shininess)
	{
		// create the black texture as default specular and emission map
		m_SpecularMap = Texture2D::CreateFlatColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_EmissionMap = Texture2D::CreateFlatColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	}

	void Material::SetDiffuseMap(Ref<Texture2D> texture)
	{
		m_DiffuseMap = texture;
	}

	void Material::SetSpecularMap(Ref<Texture2D> texture)
	{
		m_SpecularMap = texture;
	}

	void Material::SetEmissionMap(Ref<Texture2D> texture)
	{
		m_EmissionMap = texture;
	}

	void Material::Bind()
	{
		m_Shader->Bind();

		// diffuse
		HZ_CORE_ASSERT(m_DiffuseMap, "Material has no diffuse map!");
		m_DiffuseMap->Bind(s_DiffuseSlot);
		m_Shader->SetInt("u_Material.diffuse", s_DiffuseSlot);
		// specular
		m_SpecularMap->Bind(s_SpecularSlot);
		m_Shader->SetInt("u_Material.specular", s_SpecularSlot);
		m_Shader->SetFloat("u_Material.shininess", m_Shininess);
		// emission
		m_EmissionMap->Bind(s_EmissionSlot);
		m_Shader->SetInt("u_Material.emission", s_EmissionSlot);

		m_DiffuseMap->Bind(s_DiffuseSlot);
	}

}


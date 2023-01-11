#include "hzpch.h"
#include "Material.h"
#include "Renderer.h"

namespace Hazel {

	Material::Material(Ref<Texture2D> diffuseMap, Ref<Texture2D> specularMap, Ref<Texture2D> emissionMap, float shininess)
		: m_Shininess(shininess)
	{
		// create the black texture as default specular and emission map
		auto blackTexture = Texture2D::CreateFlatColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_DiffuseMap = (diffuseMap) ? diffuseMap : blackTexture;
		m_SpecularMap = (specularMap) ? specularMap : blackTexture;
		m_EmissionMap = (emissionMap) ? emissionMap : blackTexture;
		
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

	void Material::Bind(const Ref<Shader>& shader)
	{
		shader->Bind();

		// diffuse
		HZ_CORE_ASSERT(m_DiffuseMap, "Material has no diffuse map!");
		m_DiffuseMap->Bind(s_DiffuseSlot);
		shader->SetInt("u_Material.diffuse", s_DiffuseSlot);
		// specular
		m_SpecularMap->Bind(s_SpecularSlot);
		shader->SetInt("u_Material.specular", s_SpecularSlot);
		shader->SetFloat("u_Material.shininess", m_Shininess);
		// emission
		m_EmissionMap->Bind(s_EmissionSlot);
		shader->SetInt("u_Material.emission", s_EmissionSlot);

		m_DiffuseMap->Bind(s_DiffuseSlot);
	}

}


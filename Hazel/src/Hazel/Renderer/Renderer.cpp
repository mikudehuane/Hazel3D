#include "hzpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	Ref<ShaderLibrary> Renderer::s_ShaderLibrary = CreateRef<ShaderLibrary>();
	Ref<Texture2D> Renderer::s_WhiteTexture2D;
	
	void Renderer::Init()
	{
		Renderer2D::Init();

		s_ShaderLibrary->Load("Hazel/assets/shaders/Light");

		uint32_t whiteTextureData = 0xffffffff;
		s_WhiteTexture2D = Texture2D::Create(1, 1, &whiteTextureData);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const Camera& camera, const Light& globalLight)
	{
		for (auto& [shaderName, shader] : Renderer::GetShaderLib()->GetShaders())
		{
			shader->Bind();
			shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
			shader->SetFloat3("u_LightColor", globalLight.GetColor());
		}
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(
		const Ref<VertexArray>& vertexArray,
		const Ref<Material>& material,
		const glm::mat4& modelTransform
	)
	{
		material->Bind();
		material->GetShader()->SetMat4("u_Transform", modelTransform);
		
		vertexArray->Bind();

		if (vertexArray->GetIndexBuffer())
		{
			RenderCommand::DrawIndexed(vertexArray->GetIndexBuffer()->GetCount());
		}
		else
		{
			RenderCommand::Draw(0, vertexArray->GetVertexCount());
		}
	}

}
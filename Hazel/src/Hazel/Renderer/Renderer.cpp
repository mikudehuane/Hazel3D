#include "hzpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	Ref<ShaderLibrary> Renderer::s_ShaderLibrary = CreateRef<ShaderLibrary>();
	
	void Renderer::Init()
	{
		Renderer2D::Init();

		s_ShaderLibrary->Load("Hazel/assets/shaders/Light");
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(const Camera& camera, const Light& light)
	{
		for (auto& [shaderName, shader] : Renderer::GetShaderLib()->GetShaders())
		{
			shader->Bind();
			shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
			shader->SetFloat3("u_ViewPosition", camera.GetPosition());

			shader->SetFloat3("u_Light.color", light.GetColor());
			shader->SetFloat3("u_Light.position", light.GetPosition());
			shader->SetFloat("u_Light.ambient", light.GetAmbientIntensity());
			shader->SetFloat("u_Light.diffuse", light.GetDiffuseIntensity());
			shader->SetFloat("u_Light.specular", light.GetSpecularIntensity());
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
		// TODO(islander): validate
		glm::mat3 modelTransformNormal = glm::transpose(glm::inverse(glm::mat3(modelTransform)));
		material->GetShader()->SetMat3("u_TransformNormal", modelTransformNormal);
		
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
#include "hzpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace Hazel {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	Ref<ShaderLibrary> Renderer::s_ShaderLibrary = CreateRef<ShaderLibrary>();
	
	void Renderer::Init()
	{
		Renderer2D::Init();

		s_ShaderLibrary->Load("Hazel/assets/shaders/Material");
		s_ShaderLibrary->Load("Hazel/assets/shaders/Light");
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	// TODO(islander): decouple different lights and use separate shaders
	void Renderer::BeginScene(
		const Camera& camera,
		// lighting
		const Ref<DirectionalLight>& directionalLight,
		const std::vector<Ref<PointLight>>& pointLights,
		const Ref<SpotLight>& spotLight
	)
	{
		for (auto& [shaderName, shader] : Renderer::GetShaderLib()->GetShaders())
		{
			shader->Bind();
			// camera
			shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
			shader->SetFloat3("u_ViewPosition", camera.GetPosition());

			// directional light
			if (directionalLight)
			{
				directionalLight->Bind(shader);
			}
			shader->SetInt("u_PointLightCount", pointLights.size());
			for (int i = 0; i < pointLights.size(); ++i)
			{
				const auto& pointLight = pointLights[i];
				pointLight->Bind(shader, i);
			}
			if (spotLight)
			{
				shader->SetInt("u_SpotLightCount", 1);  // TODO(islander): as an array
				spotLight->Bind(shader);
			}
		}
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(
		const Ref<Mesh>& mesh,
		const glm::mat4& modelTransform
	)
	{
		auto shader = Hazel::Renderer::GetShaderLib()->Get("Material");
		mesh->GetMaterial()->Bind(shader);
		shader->SetMat4("u_Transform", modelTransform);
		// TODO(islander): validate
		glm::mat3 modelTransformNormal = glm::transpose(glm::inverse(glm::mat3(modelTransform)));
		shader->SetMat3("u_TransformNormal", modelTransformNormal);
		
		DrawVertexArray(mesh->GetVertexArray());
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Light>& light, const glm::mat4& modelTransform)
	{
		auto shader = Hazel::Renderer::GetShaderLib()->Get("Light");
		shader->Bind();
		shader->SetMat4("u_Transform", modelTransform);
		shader->SetFloat3("u_Color", light->GetColor());
		DrawVertexArray(vertexArray);
	}

	void Renderer::DrawVertexArray(const Ref<VertexArray>& vertexArray)
	{
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
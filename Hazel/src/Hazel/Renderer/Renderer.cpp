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
		const Ref<DirectionalLight>& directionalLight)
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
			//shader->SetFloat3("u_Light.color", light->GetColor());
			//shader->SetFloat4("u_Light.position", light->GetPosition());
			//shader->SetFloat("u_Light.ambient", light->GetAmbientIntensity());
			//shader->SetFloat("u_Light.diffuse", light->GetDiffuseIntensity());
			//shader->SetFloat("u_Light.specular", light->GetSpecularIntensity());
			//// TODO(islander): strange op, decouple attenuation from directional light!
			//if (light->GetType() == Light::Directional)
			//{
			//	// placeholder values (designed to make the computation correct)
			//	shader->SetFloat("u_Light.constant", 1.0f);
			//	shader->SetFloat("u_Light.linear", 0.0f);
			//	shader->SetFloat("u_Light.quadratic", 0.0f);
			//	shader->SetFloat3("u_Light.direction", { 1.0f, 0.0f, 0.0f });
			//	shader->SetFloat("u_Light.cutOff", -1.0f);
			//	shader->SetFloat("u_Light.outerCutOff", -1.0f);
			//}
			//else if (light->GetType() == Light::Point)
			//{
			//	Ref<PointLight> pLight = std::dynamic_pointer_cast<PointLight>(light);
			//	shader->SetFloat("u_Light.constant", pLight->GetConstant());
			//	shader->SetFloat("u_Light.linear", pLight->GetLinear());
			//	shader->SetFloat("u_Light.quadratic", pLight->GetQuadratic());
			//	// placeholder values (designed to make the computation correct)
			//	shader->SetFloat3("u_Light.direction", { 1.0f, 0.0f, 0.0f });
			//	shader->SetFloat("u_Light.cutOff", -1.0f);
			//	shader->SetFloat("u_Light.outerCutOff", -1.0f);
			//}
			//else if (light->GetType() == Light::Spot)
			//{
			//	Ref<SpotLight> sLight = std::dynamic_pointer_cast<SpotLight>(light);
			//	shader->SetFloat("u_Light.constant", sLight->GetConstant());
			//	shader->SetFloat("u_Light.linear", sLight->GetLinear());
			//	shader->SetFloat("u_Light.quadratic", sLight->GetQuadratic());
			//	shader->SetFloat3("u_Light.direction", sLight->GetDirection());
			//	shader->SetFloat("u_Light.cutOff", sLight->GetCutOff());
			//	shader->SetFloat("u_Light.outerCutOff", sLight->GetOuterCutOff());
			//}
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
		auto shader = Hazel::Renderer::GetShaderLib()->Get("Material");
		material->Bind(shader);
		shader->SetMat4("u_Transform", modelTransform);
		// TODO(islander): validate
		glm::mat3 modelTransformNormal = glm::transpose(glm::inverse(glm::mat3(modelTransform)));
		shader->SetMat3("u_TransformNormal", modelTransformNormal);
		
		DrawVertexArray(vertexArray);
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Light>& light, const glm::mat4& modelTransform)
	{
		auto shader = Hazel::Renderer::GetShaderLib()->Get("Light");
		shader->Bind();
		shader->SetMat4("u_Transform", modelTransform);
		
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
#include "hzpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {
	
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		RenderCommand::Init();

		s_Data = new Renderer2DStorage();
		
		s_Data->QuadVertexArray = Hazel::VertexArray::Create();

		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Hazel::Ref<Hazel::VertexBuffer> squareVB;
		squareVB = Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
		Hazel::Ref<Hazel::IndexBuffer> squareIB;
		squareIB = Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);
		
		Renderer::GetShaderLib()->Load("Hazel/assets/shaders/Material");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		for (auto& [shaderName, shader] : Renderer::GetShaderLib()->GetShaders())
		{
			shader->Bind();
			shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		}
	}

	void Renderer2D::EndScene()
	{
	}

	static inline void SetPosSize(const Ref<Shader>& shader, const glm::vec3& position, const glm::vec2& size)
	{
		shader->SetMat4(
			"u_Transform",
			glm::scale(
				glm::translate(glm::mat4(1.0f), position),
				{ size.x, size.y, 1.0f }
			)
		);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Material>& material)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, material);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Material>& material)
	{
		material->Bind();
		SetPosSize(Renderer::GetShaderLib()->Get("Material"), position, size);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}
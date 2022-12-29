#include "Sandbox3D.h"

Sandbox3D::Sandbox3D()
	: m_CameraController((float)Hazel::DEFAULT_WINDOW_WIDTH / (float)Hazel::DEFAULT_WINDOW_HEIGHT, true),
	Layer("Example"), m_SquarePosition(0.0f)
{
	m_SquareVA = Hazel::VertexArray::Create();

	float texCoord = 5.0f;
	float squareVertices[4 * 5] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, texCoord, 0.0f,
		 0.5f,  0.5f, 0.0f, texCoord, texCoord,
		-0.5f,  0.5f, 0.0f, 0.0f, texCoord
	};
	Hazel::Ref<Hazel::VertexBuffer> squareVB;
	squareVB = Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ Hazel::ShaderDataType::Float3, "a_Position" },
		{ Hazel::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Hazel::Ref<Hazel::IndexBuffer> squareIB;
	squareIB = Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

	std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	auto flatColorShader = Hazel::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
	Hazel::Renderer::GetShaderLib()->Add(flatColorShader);

	auto textureShader = Hazel::Renderer::GetShaderLib()->Load("assets/shaders/Texture");
	auto mixedTextureShader = Hazel::Renderer::GetShaderLib()->Load("assets/shaders/MixedTexture");

	m_Texture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
	m_ChernoLogoTexture = Hazel::Texture2D::Create("assets/textures/ChernoLogo.png");

	m_ChernoLogoTexture->Bind();
	m_ChernoLogoTexture->SetTexWrapT(HZ_MIRRORED_REPEAT);

	std::dynamic_pointer_cast<Hazel::OpenGLShader>(textureShader)->Bind();
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
}

void Sandbox3D::OnUpdate(Hazel::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	auto flatColorShader = Hazel::Renderer::GetShaderLib()->Get("FlatColor");

	std::dynamic_pointer_cast<Hazel::OpenGLShader>(flatColorShader)->Bind();
	std::dynamic_pointer_cast<Hazel::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; ++y)
	{
		for (int x = 0; x < 20; ++x)
		{
			glm::vec3 pos(y * 0.11f, x * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Hazel::Renderer::Submit(flatColorShader, m_SquareVA, transform);
		}
	}

	auto textureShader = Hazel::Renderer::GetShaderLib()->Get("Texture");

	m_Texture->Bind();
	Hazel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_ChernoLogoTexture->Bind();
	Hazel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Hazel::Renderer::EndScene();
}

void Sandbox3D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox3D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}


#include "Sandbox3D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D()
	: m_Camera(true),
	//m_CameraController((float)Hazel::DEFAULT_WINDOW_WIDTH / (float)Hazel::DEFAULT_WINDOW_HEIGHT, true),
	Layer("Sandbox3D")
{
	float aspectRatio = (float)Hazel::DEFAULT_WINDOW_WIDTH / (float)Hazel::DEFAULT_WINDOW_HEIGHT;
	m_Camera.SetPerspectiveProjection(aspectRatio, 45.0f, 0.1f, 1000.0f);
}

void Sandbox3D::OnAttach()
{
	// vertex array
	m_SquareVA = Hazel::VertexArray::Create();
	// vertex buffer
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
	m_SquareVA->AddVertexBuffer(squareVB);
	// index buffer
	uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
	Hazel::Ref<Hazel::IndexBuffer> squareIB;
	squareIB = Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	// material
	m_TexMaterial = Hazel::CreateRef<Hazel::Material>(Hazel::Renderer::GetShaderLib()->Get("Material"));
	auto texture = Hazel::Texture2D::Create("Sandbox/assets/textures/LaughContainer.png");
	m_TexMaterial->SetTexture(texture);
}

void Sandbox3D::OnUpdate(Hazel::Timestep ts)
{
	// TODO(islander)
	//m_CameraController.OnUpdate(ts);

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();
	
	m_Camera.SetPerspective(m_isPerspective);
	float aspectRatio = (float)Hazel::DEFAULT_WINDOW_WIDTH / (float)Hazel::DEFAULT_WINDOW_HEIGHT;
	m_Camera.SetOrthographicProjection(
		-aspectRatio * m_ZoomLevel,
		aspectRatio * m_ZoomLevel,
		-m_ZoomLevel,
		m_ZoomLevel,
		0.1f,
		1000.0f
	);
	m_Camera.SetPosition(m_CameraPos);
	m_CameraAxis = glm::normalize(m_CameraAxis);
	m_Camera.SetRotation(glm::angleAxis(glm::radians(m_CameraAngle), m_CameraAxis));

	Hazel::Renderer::BeginScene(m_Camera);
	Hazel::Renderer::Submit(
		m_SquareVA, m_TexMaterial,
		glm::translate(glm::mat4(1.0f), m_SquarePos)
	);
	Hazel::Renderer::EndScene();
}

void Sandbox3D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::Checkbox("Perspective", &m_isPerspective);
	ImGui::SliderFloat("Zoom Level", &m_ZoomLevel, 1.0f, 100.0f);
	ImGui::DragFloat3("Square Position", glm::value_ptr(m_SquarePos), 0.1f);
	ImGui::DragFloat3("Camera Position", glm::value_ptr(m_CameraPos), 0.1f);
	ImGui::DragFloat3("Camera Axis", glm::value_ptr(m_CameraAxis), 0.1f);
	ImGui::SliderFloat("Camera Angle", &m_CameraAngle, -360.0f, 360.0f);
	ImGui::End();
}

void Sandbox3D::OnEvent(Hazel::Event& e)
{
	// TODO(islander)
	//m_CameraController.OnEvent(e);
}


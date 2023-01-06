#include "Sandbox3D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D(): 
	m_CameraController(
		true, (float)Hazel::DEFAULT_WINDOW_WIDTH / (float)Hazel::DEFAULT_WINDOW_HEIGHT
	), Layer("Sandbox3D")
{
	float aspectRatio = (float)Hazel::DEFAULT_WINDOW_WIDTH / (float)Hazel::DEFAULT_WINDOW_HEIGHT;
}

void Sandbox3D::OnAttach()
{
	// vertex array
	m_SquareVA = Hazel::VertexArray::Create();
	// vertex buffer
	float squareVertices[4 * 5] = {
		-3.0f, -3.0f, 0.0f, 0.0f, 0.0f,
		 3.0f, -3.0f, 0.0f, 1.0f, 0.0f,
		 3.0f,  3.0f, 0.0f, 1.0f, 1.0f,
		-3.0f,  3.0f, 0.0f, 0.0f, 1.0f
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

	Hazel::Camera& m_Camera = m_CameraController.GetCamera();
	
	m_CameraController.SetPerspective(m_isPerspective);
	float aspectRatio = (float)Hazel::DEFAULT_WINDOW_WIDTH / (float)Hazel::DEFAULT_WINDOW_HEIGHT;

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
	ImGui::DragFloat3("Square Position", glm::value_ptr(m_SquarePos), 0.1f);
	// show the current camera position
	const glm::vec3& cameraPos = m_CameraController.GetCamera().GetPosition();
	ImGui::Text("Camera Position: (%.1f, %.1f, %.1f)", cameraPos.x, cameraPos.y, cameraPos.z);
	const glm::quat& cameraRotation = m_CameraController.GetCamera().GetRotation();
	ImGui::Text("Camera Rotation (wxyz): (%.2f, %.2f, %.2f, %.2f)", cameraRotation.w, cameraRotation.x, cameraRotation.y, cameraRotation.z);
	ImGui::Text("Camera Rotation Norm: %.2f", glm::length(cameraRotation));
	ImGui::End();
}

void Sandbox3D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}


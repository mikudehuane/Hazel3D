#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController((float)Hazel::DEFAULT_WINDOW_WIDTH / (float)Hazel::DEFAULT_WINDOW_HEIGHT, true)
{
}

void Sandbox2D::OnAttach()
{
	m_BoxMaterial = Hazel::CreateRef<Hazel::Material>(Hazel::Renderer::GetShaderLib()->Get("Material"));
	auto texture = Hazel::Texture2D::Create("Sandbox/assets/textures/laugh.png");
	m_BoxMaterial->SetTexture(texture);

	m_ColorMaterial = Hazel::CreateRef<Hazel::Material>(Hazel::Renderer::GetShaderLib()->Get("Material"));

	m_MixedMaterial = Hazel::CreateRef<Hazel::Material>(Hazel::Renderer::GetShaderLib()->Get("Material"));
	texture = Hazel::Texture2D::Create("Sandbox/assets/textures/container.png");
	m_MixedMaterial->SetTexture(texture);
}

void Sandbox2D::OnDetach()
{
	Hazel::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	m_MixedMaterial->SetColor(m_SquareColor, 0.5);
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_MixedMaterial);
	m_ColorMaterial->SetColor(m_SquareColor);
	Hazel::Renderer2D::DrawQuad({ -1.0f, 0.5f }, { 0.4f, 0.8f }, m_ColorMaterial);
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 2.0f, 2.0f }, m_BoxMaterial);
	Hazel::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}

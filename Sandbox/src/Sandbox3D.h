#pragma once

#include <Hazel.h>

#include "imgui/imgui.h"

#include <memory>

class Sandbox3D : public Hazel::Layer
{
public:
	Sandbox3D();

	virtual void OnAttach() override;
	virtual void OnUpdate(Hazel::Timestep ts) override;

	virtual void OnImGuiRender() override;

	virtual void OnEvent(Hazel::Event& e) override;

private:
	Hazel::CameraController m_CameraController;
	bool m_isPerspective = true;
	glm::vec3 m_CameraAxis = glm::vec3(0.0f, 0.0f, -1.0f);
	float m_CameraAngle = 0.0f;

	Hazel::Ref<Hazel::VertexArray> m_SquareVA;
	Hazel::Ref<Hazel::Material> m_TexMaterial;
	glm::vec3 m_SquarePos = glm::vec3(0.0f, 0.0f, 0.0f);
};


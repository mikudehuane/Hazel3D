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
	Hazel::Camera m_Camera;
	bool m_isPerspective = true;
	float m_ZoomLevel = 1.0f;  // works for orthographic camera only

	Hazel::Ref<Hazel::VertexArray> m_SquareVA;
	Hazel::Ref<Hazel::Material> m_TexMaterial;
	glm::vec3 m_SquarePos = glm::vec3(0.0f, 0.0f, -5.0f);
};


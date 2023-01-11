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
	virtual void OnDetach() override;

	virtual void OnImGuiRender() override;

	virtual void OnEvent(Hazel::Event& e) override;

private:
	Hazel::CameraController m_CameraController;
	bool m_isPerspective = true;

	Hazel::Ref<Hazel::VertexArray> m_BoxVA;
	Hazel::Ref<Hazel::Material> m_BoxMaterial;
	glm::vec3 m_BoxPos = glm::vec3(0.0f, 0.0f, 0.0f);

	Hazel::Ref<Hazel::Light> m_Light;
	Hazel::Ref<Hazel::VertexArray> m_LightVA;
	Hazel::Ref<Hazel::Material> m_LightMaterial;
	glm::vec3 m_LightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 m_LightPos = glm::vec3(1.0f, 1.0f, 1.0f);
	struct {
		float ambient, diffuse, specular;
	} m_LightIntensity = { 0.1f, 1.0f, 0.5f };
};


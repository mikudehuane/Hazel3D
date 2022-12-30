#pragma once

#include <Hazel.h>

#include "imgui/imgui.h"

#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

class Sandbox3D : public Hazel::Layer
{
public:
	Sandbox3D();

	void OnUpdate(Hazel::Timestep ts) override;

	virtual void OnImGuiRender() override;

	virtual void OnEvent(Hazel::Event& e) override;

private:
	Hazel::OrthographicCameraController m_CameraController;
};


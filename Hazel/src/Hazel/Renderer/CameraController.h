#pragma once

#include "Hazel/Renderer/Camera.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Core/Core.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel {

	// Camera will be be initially placed at -sqrt(zNear * zFar)
	// In orthographic mode, screen height is the height in **view space** at z=0 (word space)
	class CameraController
	{
	public:
		// aspectRatio: width / height
		CameraController(
			bool isPerspective,
			// stored for perspective
			float aspectRatio, float fovy = 45.0f, float zNear = 0.1f, float zFar = 1000.0f
		);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline Camera& GetCamera() { return *m_Camera; }
		inline const Camera& GetCamera() const { return *m_Camera; }

		void SetPosition(const glm::vec3& position);
		void SetPerspective(bool isPerspective);
	private:
		glm::mat4 ComputePerspectiveProjectionMatrix();
		glm::mat4 ComputeOrthographicProjectionMatrix();

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		bool m_IsPerspective;
		float m_AspectRatio;
		float m_Fovy, m_Near, m_Far;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		Scope<Camera> m_Camera;

		//float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed = 180.0f;
	};

}

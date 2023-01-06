#pragma once

#include "Hazel/Renderer/Camera.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Core/Core.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

#include "Hazel/Core/MouseButtonCodes.h"

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

		inline const glm::vec3& GetCameraX() const { return m_CameraX; }
		inline const glm::vec3& GetCameraY() const { return m_CameraY; }
		inline const glm::vec3& GetCameraZ() const { return m_CameraZ; }

		inline const float GetZoomLevel() const { return m_ZoomLevel; }
		inline const float GetFovy() const { return m_Fovy; }
		inline const float GetAspectRatio() const { return m_AspectRatio; }

		// TODO(islander): add euler angle supports
	private:
		glm::mat4 ComputePerspectiveProjectionMatrix();
		glm::mat4 ComputeOrthographicProjectionMatrix();
		void ResetProjectionMatrix();

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		// m_MouseButtonPressed is set only in OnMouseButtonPressed (except for HZ_MOUSE_BUTTON_NONE)
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
	private:
		//---------------- camera property -------------
		bool m_IsPerspective;
		float m_AspectRatio;
		float m_Fovy, m_Near, m_Far;
		float m_ZoomLevel;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		Scope<Camera> m_Camera;

		//---------------- camera speeds ---------------
		// relative to pixel
		float m_CameraTranslationSpeedXY = 0.01f;  
		float m_CameraRotationSpeedXY = 0.1f;
		// relative to scrolling
		float m_ZoomSensitivity = 0.1f, m_ZoomMin = 0.1f;  
		float m_FovySensitiviy = 1.0f, m_FovyMax = 179.0f, m_FovyMin = 1.0f;

		//---------------- camera states ---------------
		// xyz-axis of camera (used for translation)
		glm::vec3 m_CameraX = { 1.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraY = { 0.0f, 1.0f, 0.0f };
		glm::vec3 m_CameraZ = { 0.0f, 0.0f, -1.0f };

		//---------------- input states ----------------
		// Which button is currently pressed (record the first button that is pressed only)
		int m_MouseButtonPressed = HZ_MOUSE_BUTTON_NONE;
		// TODO(islander): The value is passed as int, but use float for generally
		glm::vec2 m_MouseButtonPressedPosition = glm::i32vec2(0.0f, 0.0f);
	};

}

#include "hzpch.h"
#include "CameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/Window.h"
#include "Hazel/Core/Core.h"

#include <cmath>

#include <glm/gtc/quaternion.hpp>

namespace Hazel {

	CameraController::CameraController(bool isPerspective, float aspectRatio, float fovy, float zNear, float zFar)
		: m_AspectRatio(aspectRatio), m_IsPerspective(isPerspective),
		m_Fovy(fovy), m_Near(zNear), m_Far(zFar)
	{
		// zMiddle is the default camera position
		float zMiddle = std::sqrt(m_Near * m_Far);
		// set zoom level to the height at z=0
		float halfHeight = zMiddle * std::tan(glm::radians(m_Fovy) / 2.0f);
		m_ZoomLevel = std::max(halfHeight, m_ZoomMin);  // clamp

		if (m_IsPerspective)
		{
			m_Camera = CreateScope<Camera>(ComputePerspectiveProjectionMatrix());
		}
		else
		{
			m_Camera = CreateScope<Camera>(ComputeOrthographicProjectionMatrix());
		}
		
		SetPosition({0.0f, 0.0f, zMiddle});
	}

	void CameraController::OnUpdate(Timestep ts)
	{
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(CameraController::OnWindowResized));
		dispatcher.Dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(CameraController::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(CameraController::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(CameraController::OnMouseMoved));
	}

	void CameraController::SetPosition(const glm::vec3& position)
	{
		m_CameraPosition = position;
		m_Camera->SetPosition(m_CameraPosition);
	}

	void CameraController::SetRotation(const glm::quat& rotation)
	{
		m_Camera->SetRotation(rotation);
	}

	void CameraController::SetPerspective(bool isPerspective)
	{
		if (isPerspective != m_IsPerspective)  // reset the projection matrix only if the state changes
		{
			m_IsPerspective = isPerspective;
			ResetProjectionMatrix();
		}
	}

	glm::mat4 CameraController::ComputePerspectiveProjectionMatrix()
	{
		return glm::perspective(glm::radians(m_Fovy), m_AspectRatio, m_Near, m_Far);
	}

	glm::mat4 CameraController::ComputeOrthographicProjectionMatrix()
	{
		return glm::ortho(
			-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel,
			m_Near, m_Far
		);
	}

	void CameraController::ResetProjectionMatrix()
	{
		if (m_IsPerspective)
		{
			glm::mat4 projectionMatrix = ComputePerspectiveProjectionMatrix();
			m_Camera->SetProjection(projectionMatrix);
		}
		else
		{
			glm::mat4 projectionMatrix = ComputeOrthographicProjectionMatrix();
			m_Camera->SetProjection(projectionMatrix);
		}
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		if (m_IsPerspective)
		{
			m_Fovy -= e.GetYOffset() * m_FovySensitiviy;
			m_Fovy = std::max(m_Fovy, m_FovyMin);
			m_Fovy = std::min(m_Fovy, m_FovyMax);
			m_Camera->SetProjection(ComputePerspectiveProjectionMatrix());
		}
		else
		{
			m_ZoomLevel -= e.GetYOffset() * m_ZoomSensitivity;
			m_ZoomLevel = std::max(m_ZoomLevel, m_ZoomMin);
			m_Camera->SetProjection(ComputeOrthographicProjectionMatrix());
		}
		return true;
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		ResetProjectionMatrix();
		return false;
	}

	bool CameraController::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (m_MouseButtonPressed == HZ_MOUSE_BUTTON_NONE)  // ignore multiple buttons
		{
			m_MouseButtonPressed = e.GetMouseButton();
			m_MouseButtonPressedPosition = { Input::GetMouseX(), Input::GetMouseY() };
		}
		return true;
	}

	bool CameraController::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		if (m_MouseButtonPressed == e.GetMouseButton())  // only handle current button
		{
			m_MouseButtonPressed = HZ_MOUSE_BUTTON_NONE;
		}
		return true;
	}

	bool CameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		// check for mouse state
		if (m_MouseButtonPressed != HZ_MOUSE_BUTTON_NONE)
		{
			if (!Input::IsMouseButtonPressed(m_MouseButtonPressed))
			{
				HZ_CORE_WARN("CameraController::OnMouseMoved: Key {0} is not pressed, reset m_MouseButtonPressed to HZ_MOUSE_BUTTON_NONE.", m_MouseButtonPressed);
				HZ_CORE_ASSERT(0, "CameraController::OnMouseMoved: Key {0} is not pressed, reset m_MouseButtonPressed to HZ_MOUSE_BUTTON_NONE.", m_MouseButtonPressed);
				m_MouseButtonPressed = HZ_MOUSE_BUTTON_NONE;
			}
		}

		switch (m_MouseButtonPressed)
		{
		case HZ_MOUSE_BUTTON_MIDDLE:  // translation
		{
			float dx = e.GetX() - m_MouseButtonPressedPosition.x;
			float dy = e.GetY() - m_MouseButtonPressedPosition.y;
			m_CameraPosition -= dx * m_CameraTranslationSpeedXY * m_Camera->GetXAxis();
			m_CameraPosition += dy * m_CameraTranslationSpeedXY * m_Camera->GetYAxis();
			m_Camera->SetPosition(m_CameraPosition);
			m_MouseButtonPressedPosition = { e.GetX(), e.GetY() };
			return true;
		}
		case HZ_MOUSE_BUTTON_RIGHT:  // rotation
		{
			float dx = e.GetX() - m_MouseButtonPressedPosition.x;
			float dy = e.GetY() - m_MouseButtonPressedPosition.y;
			m_MouseButtonPressedPosition = { e.GetX(), e.GetY() };

			// compute the added rotation
			// horizental rotation: around the current y axis
			glm::quat rotationY = glm::angleAxis(glm::radians(-dx * m_CameraRotationSpeedXY), m_Camera->GetYAxis());
			// vertical rotation: around the world x axis
			glm::quat rotationX = glm::angleAxis(glm::radians(-dy * m_CameraRotationSpeedXY), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::quat addedRotation = rotationX * rotationY;

			// update the view projection
			glm::quat cameraRotation = addedRotation * m_Camera->GetRotation();
			SetRotation(cameraRotation);
			return true;
		}
		default: return false;
		}
	}

}

#include "hzpch.h"
#include "CameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/Window.h"
#include "Hazel/Core/Core.h"

#include <cmath>

namespace Hazel {

	CameraController::CameraController(bool isPerspective, float aspectRatio, float fovy, float zNear, float zFar)
		: m_AspectRatio(aspectRatio), m_IsPerspective(isPerspective),
		m_Fovy(fovy), m_Near(zNear), m_Far(zFar)
	{
		if (m_IsPerspective)
		{
			m_Camera = CreateScope<Camera>(ComputePerspectiveProjectionMatrix());
		}
		else
		{
			m_Camera = CreateScope<Camera>(ComputeOrthographicProjectionMatrix());
		}
		
		// reset the position
		float zMiddle = std::sqrt(m_Near * m_Far);
		SetPosition({0.0f, 0.0f, zMiddle});
	}

	void CameraController::OnUpdate(Timestep ts)
	{
		
	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(CameraController::OnMouseScrolled));
		//dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(CameraController::OnWindowResized));
	}

	void CameraController::SetPosition(const glm::vec3& position)
	{
		m_CameraPosition = position;
		m_Camera->SetPosition(m_CameraPosition);
		if (!m_IsPerspective) // reset the orthographic projection
		{
			glm::mat4 projectionMatrix = ComputeOrthographicProjectionMatrix();
			// TODO(islander): using move constructor may save one copy (need to modify the glm lib)
			m_Camera->SetProjection(projectionMatrix);
		}
	}

	void CameraController::SetPerspective(bool isPerspective)
	{
		if (isPerspective != m_IsPerspective)  // reset the projection matrix only if the state changes
		{
			m_IsPerspective = isPerspective;
			
			if (m_IsPerspective)
			{
				glm::mat4 projectionMatrix = ComputePerspectiveProjectionMatrix();
				// TODO(islander): perspective projection is usually invariant, cache it in class
				m_Camera->SetProjection(projectionMatrix);
			}
			else
			{
				glm::mat4 projectionMatrix = ComputeOrthographicProjectionMatrix();
				m_Camera->SetProjection(projectionMatrix);
			}
		}
	}

	glm::mat4 CameraController::ComputePerspectiveProjectionMatrix()
	{
		return glm::perspective(glm::radians(m_Fovy), m_AspectRatio, m_Near, m_Far);
	}

	glm::mat4 CameraController::ComputeOrthographicProjectionMatrix()
	{
		float halfHeight = m_CameraPosition.z * std::tan(glm::radians(m_Fovy) / 2.0f);
		halfHeight = std::max(halfHeight, 0.1f);  // clamp

		return glm::ortho(
			-m_AspectRatio * halfHeight, m_AspectRatio * halfHeight, 
			-halfHeight, halfHeight, 
			m_Near, m_Far
		);
	}

	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_CameraPosition.z -= 0.1f * e.GetYOffset();

		m_Camera->SetPosition(m_CameraPosition);

		return true;
	}

	//bool CameraController::OnWindowResized(WindowResizeEvent& e)
	//{
	//	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

	//	// Set for orthographic
	//	m_Camera.SetOrthographicProjection(
	//		-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
	//		-m_ZoomLevel, m_ZoomLevel, m_Near, m_Far
	//	);
	//	
	//	// Set for perspective
	//	m_Camera.SetPerspectiveProjection(
	//		m_AspectRatio, m_Fovy, m_Near, m_Far
	//	);

	//	return true;
	//}

}

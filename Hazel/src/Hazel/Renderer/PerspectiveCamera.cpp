#include "hzpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	PerspectiveCamera::PerspectiveCamera(float aspectRatio, float fovy, float zNear, float zFar)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fovy), aspectRatio, zNear, zFar)),
		  m_ViewMatrix(1.0f), m_Position(0.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::translate(
			glm::rotate(glm::mat4(1.0f), -glm::radians(m_Rotation), glm::vec3(0, 0, 1)), -m_Position);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
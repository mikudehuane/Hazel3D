#include "hzpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top)),
		  m_ViewMatrix(1.0f), m_Position(0.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::translate(
			glm::rotate(glm::mat4(1.0f), -m_Rotation, glm::vec3(0, 0, 1)), -m_Position);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
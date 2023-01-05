#include "hzpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	Camera::Camera(const glm::mat4& projectionMatrix):
		m_ViewMatrix(1.0f),
		m_Position(0.0f), m_RotationQuat(1.0f, 0.0f, 0.0f, 0.0f)
	{
		m_ProjectionMatrix = projectionMatrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetProjection(const glm::mat4& projectionMatrix)
	{
		m_ProjectionMatrix = projectionMatrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void Camera::SetRotation(const glm::quat& rotationQuat)
	{
		m_RotationQuat = rotationQuat;
		RecalculateViewMatrix();
	}
	
	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 viewRotationMatrix = glm::mat4_cast(m_RotationQuat);
		m_ViewMatrix = glm::translate(viewRotationMatrix, -m_Position);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
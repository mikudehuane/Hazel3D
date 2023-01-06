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
		glm::mat3 cameraRotationMatrix = glm::mat3_cast(rotationQuat);
		m_CameraX = cameraRotationMatrix * glm::vec3(1.0f, 0.0f, 0.0f);
		m_CameraY = cameraRotationMatrix * glm::vec3(0.0f, 1.0f, 0.0f);
		m_CameraZ = cameraRotationMatrix * glm::vec3(0.0f, 0.0f, 1.0f);
		RecalculateViewMatrix();
	}
	
	void Camera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position - m_CameraZ, m_CameraY);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
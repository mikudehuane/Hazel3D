#include "hzpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel {

	Camera::Camera(bool isPerspective, float aspectRatio, float fovy, float zNearPerspective, float zFarPerspective, float left, float right, float bottom, float top, float zNearOrthographic, float zFarOrthographic)
		: m_PerspectiveProjectionMatrix(glm::perspective(glm::radians(fovy), aspectRatio, zNearPerspective, zFarPerspective)),
		  m_OrthographicProjectionMatrix(glm::ortho(left, right, bottom, top, zNearOrthographic, zFarOrthographic)),
		  m_ViewMatrix(1.0f), m_Position(0.0f),
		  m_IsPerspective(isPerspective), m_RotationQuat(1.0f, 0.0f, 0.0f, 0.0f)
	{
		if (m_IsPerspective)
		{
			m_ProjectionMatrix = &m_PerspectiveProjectionMatrix;
		}
		else
		{
			m_ProjectionMatrix = &m_OrthographicProjectionMatrix;
		}

		m_ViewProjectionMatrix = (*m_ProjectionMatrix) * m_ViewMatrix;
	}

	void Camera::SetPerspective(bool isPerspective)
	{
		m_IsPerspective = isPerspective;
		if (m_IsPerspective)
		{
			m_ProjectionMatrix = &m_PerspectiveProjectionMatrix;
		}
		else
		{
			m_ProjectionMatrix = &m_OrthographicProjectionMatrix;
		}
		m_ViewProjectionMatrix = (*m_ProjectionMatrix) * m_ViewMatrix;
	}

	void Camera::SetOrthographicProjection(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		m_OrthographicProjectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
		m_ViewProjectionMatrix = *m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetPerspectiveProjection(float aspectRatio, float fovy, float zNear, float zFar)
	{
		m_PerspectiveProjectionMatrix = glm::perspective(glm::radians(fovy), aspectRatio, zNear, zFar);
		m_ViewProjectionMatrix = *m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewProjectionMatrix();
	}

	void Camera::SetRotation(const glm::quat& rotationQuat)
	{
		m_RotationQuat = rotationQuat;
		RecalculateViewProjectionMatrix();
	}
	
	void Camera::RecalculateViewProjectionMatrix()
	{
		glm::mat4 viewRotationMatrix = glm::mat4_cast(m_RotationQuat);
		m_ViewMatrix = glm::translate(viewRotationMatrix, -m_Position);

		m_ViewProjectionMatrix = *m_ProjectionMatrix * m_ViewMatrix;
	}

}
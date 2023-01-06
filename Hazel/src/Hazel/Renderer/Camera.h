#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Hazel {

	class Camera
	{
	public:
		Camera(const glm::mat4& projectionMatrix = glm::mat4(1.0f));
		
		void SetProjection(const glm::mat4& projectionMatrix);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position);

		// Set the rotation for the view
		void SetRotation(const glm::quat& rotationQuat);
		inline const glm::quat& GetRotation() { return m_RotationQuat; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		glm::quat m_RotationQuat;
	};

}

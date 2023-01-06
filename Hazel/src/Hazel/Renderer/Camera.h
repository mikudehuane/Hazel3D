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

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		inline const glm::vec3& GetXAxis() const { return m_CameraX; }
		inline const glm::vec3& GetYAxis() const { return m_CameraY; }
		inline const glm::vec3& GetZAxis() const { return m_CameraZ; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		glm::quat m_RotationQuat;

		glm::vec3 m_CameraX = { 1.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraY = { 0.0f, 1.0f, 0.0f };
		glm::vec3 m_CameraZ = { 0.0f, 0.0f, 1.0f };  // point to the camera back

	};

}

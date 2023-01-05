#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Hazel {

	class Camera
	{
	public:
		Camera(
			bool isPerspective,
			// stored for perspective
			float aspectRatio = 1.0f, float fovy = 45.0f, float zNearPerspective = 0.1f, float zFarPerspective = 1000.0f,
			// stored for othographic
			float left = -1.0f, float right = 1.0f, float bottom = -0.1f, float top = 0.1f, float zNearOrthographic = 0.1f, float zFarOrthographic = 1000.0f
		);
		
		void SetPerspective(bool isPerspective);
		void SetOrthographicProjection(float left, float right, float bottom, float top, float zNear = 0.1f, float zFar = 1000.0f);
		void SetPerspectiveProjection(float aspectRatio, float fovy = 45.0f, float zNear = 0.1f, float zFar = 1000.0f);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position);

		// Set the rotation for the view
		void SetRotation(const glm::quat& rotationQuat);

		const glm::mat4& GetProjectionMatrix() const { return *m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewProjectionMatrix();
	private:
		glm::mat4 m_PerspectiveProjectionMatrix;
		glm::mat4 m_OrthographicProjectionMatrix;
		glm::mat4* m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::quat m_RotationQuat;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;

		bool m_IsPerspective;
	};

}

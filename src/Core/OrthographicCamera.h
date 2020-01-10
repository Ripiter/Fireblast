#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Fireblast
{
	class OrthographicCamera
	{
	private:
		glm::vec3 m_Position;
		float m_Rotation;

		glm::mat4 m_Projection;
	public:
		OrthographicCamera(float left, float bottom, float right, float top);
		virtual ~OrthographicCamera();

	public:
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const float GetRotation() const { return m_Rotation; }

		inline const glm::mat4& GetView() const 
		{ 
			glm::quat rquat = glm::angleAxis(m_Rotation, glm::vec3(0, 0, 1));

			return glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(rquat);
		}

		inline const glm::mat4& GetProjection() const { return m_Projection; }

		inline const glm::mat4& GetViewProjection() const 
		{
			glm::quat rquat = glm::angleAxis(m_Rotation, glm::vec3(0, 0, 1));
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(rquat);

			return m_Projection * glm::inverse(transform);
		}

	public:
		void SetProjection(float left, float bottom, float right, float top);

		void Translate(const glm::vec3 position);
		void SetPosition(const glm::vec3 position);

		void Rotate(const float rotation);
		void SetRotation(const float rotation);
	};
}

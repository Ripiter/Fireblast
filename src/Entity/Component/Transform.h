#pragma once
#include "Entity/Component/Component.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace Fireblast
{
	class Transform : public Component
	{
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	public:
		Transform() 
			: m_Position(0.f), m_Rotation(0.f, 0.f, 0.f), m_Scale(1.0f, 1.0f, 1.0f) {}

	public:
		void SetPosition(glm::vec3 pos) { m_Position = pos; }
		void Translate(glm::vec3 value) { m_Position += value; }

		void SetRotation(glm::vec3 quat) { m_Rotation = quat; }
		void Rotate(glm::vec3 value) { m_Rotation += value; }

		void SetScale(glm::vec3 scale) { m_Scale = scale; }
		void Scale(glm::vec3 value) { m_Scale += value; }
	public:
		const glm::mat4& GetTranslationMatrix() const
		{
			return glm::translate(glm::mat4(1.0f), m_Position);
		}

		const glm::mat4& GetRotationMatrix() const
		{
			glm::quat qx = glm::angleAxis(m_Rotation.x, glm::vec3(1, 0, 0));
			glm::quat qy = glm::angleAxis(m_Rotation.y, glm::vec3(0, 1, 0));
			glm::quat qz = glm::angleAxis(m_Rotation.z, glm::vec3(0, 0, 1));

			return glm::toMat4(qx * qy * qz);
		}

		const glm::mat4& GetScaleMatrix() const
		{
			return glm::scale(glm::mat4(1.0f), m_Scale);
		}

		const glm::mat4& GetTransformMatrix() const
		{
			glm::quat rquat = glm::angleAxis(m_Rotation.x, glm::vec3(1, 0, 0));
			rquat *= glm::angleAxis(m_Rotation.y, glm::vec3(0, 1, 0));
			rquat *= glm::angleAxis(m_Rotation.z, glm::vec3(0, 0, 1));	

			return glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(rquat) * glm::scale(glm::mat4(1.0f), m_Scale);
		}
	};
}
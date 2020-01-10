#include "fbpch.h"
#include "OrthographicCamera.h"

namespace Fireblast
{
	OrthographicCamera::OrthographicCamera(float left, float bottom, float right, float top)
		: m_Position(0), m_Rotation(0), m_Projection(glm::ortho(left, right, bottom, top, -1.f, 1.f))
	{
	}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	void OrthographicCamera::SetProjection(float left, float bottom, float right, float top)
	{
		m_Projection = glm::ortho(left, right, bottom, top, -1.f, 1.f);
	}

	void OrthographicCamera::Translate(const glm::vec3 position)
	{
		m_Position += position;
	}

	void OrthographicCamera::SetPosition(const glm::vec3 position)
	{
		m_Position = position;
	}

	void OrthographicCamera::Rotate(const float rotation)
	{
		m_Rotation += rotation;
	}

	void OrthographicCamera::SetRotation(const float rotation)
	{
		m_Rotation = rotation;
	}
}
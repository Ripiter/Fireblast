#pragma once
#include "Component.h"
#include "Graphics/Vertice.h"
#include "Graphics/Api/Texture.h"

namespace Fireblast
{
	class SpriteComponent : public Component
	{
	public: // TODO: Make it so end user cannot see these
		Vertex2D m_Vertices[4];
		Texture* m_Texture;
		
	public:
		SpriteComponent(glm::vec3 centerPos, glm::vec2 size, Texture* texture)
			: m_Vertices(), m_Texture(texture)
		{
			glm::vec4 color = glm::vec4(1, 1, 1, 1);

			m_Vertices[0].Vertice = glm::vec3(centerPos.x - size.x / 2, centerPos.y + size.y / 2, centerPos.z);
			m_Vertices[0].Color = color;
			m_Vertices[0].Uv = glm::vec2(0, 1);

			m_Vertices[1].Vertice = glm::vec3(centerPos.x + size.x / 2, centerPos.y + size.y / 2, centerPos.z);
			m_Vertices[1].Color = color;
			m_Vertices[1].Uv = glm::vec2(1, 1);

			m_Vertices[2].Vertice = glm::vec3(centerPos.x + size.x / 2, centerPos.y - size.y / 2, centerPos.z);
			m_Vertices[2].Color = color;
			m_Vertices[2].Uv = glm::vec2(1, 0);

			m_Vertices[3].Vertice = glm::vec3(centerPos.x - size.x / 2, centerPos.y - size.y / 2, centerPos.z);
			m_Vertices[3].Color = color;
			m_Vertices[3].Uv = glm::vec2(0, 0);
		}

		virtual ~SpriteComponent() 
		{
			delete m_Vertices;
			delete m_Texture;
		}
	};
}
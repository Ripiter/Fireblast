#pragma once
#include "Component.h"
#include "Graphics/Vertice.h"
#include "Graphics/Api/Texture.h"

namespace Fireblast
{
	class SpriteComponent : public Component
	{
	private:
		Vertex2D* m_Vertices;
		std::string m_TextureName;
	public:
		SpriteComponent(glm::vec3 centerPos, glm::vec2 size, std::string textureName, glm::vec4 color)
			: m_Vertices(nullptr), m_TextureName(textureName)
		{
			m_Vertices = new Vertex2D[4];

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

		SpriteComponent(glm::vec3 centerPos, glm::vec2 size, std::string textureName)
			: SpriteComponent(centerPos, size, textureName, { 1.f, 1.f, 1.f, 1.f }) {}

		SpriteComponent(glm::vec3 centerPos, glm::vec2 size, glm::vec4 color)
			: SpriteComponent(centerPos, size, "", color) {}

		virtual ~SpriteComponent() { delete[] m_Vertices; }

	public:
		const Vertex2D* GetVertices() const { return m_Vertices; }
		const std::string& GetTextureName() const { return m_TextureName; }
	};
}
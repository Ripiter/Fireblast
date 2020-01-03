#pragma once
#include "Graphics/Api/RenderCommands.h"
#include "Graphics/Api/RenderAPI.h"
#include "Graphics/Vertice.h"
#include "Utils/FileUtils.h"

namespace Fireblast 
{
	class Renderer2D
	{
	public:
		Renderer2D()
			: m_Vao(NULL), m_Vbo(NULL), m_Ibo(NULL), m_FlatShader(NULL), m_VerticeAmount(0) {}

		void BeginSubmit();
		void EndSubmit();
		void Onstart();
		void OnUpdate();
		void OnDraw();

		void SubmitQuad(const glm::vec3 centerPos, const glm::vec2 size, const glm::vec4 color);
		void SubmitTriangle(const glm::vec3 centerPos, const glm::vec2 size, const glm::vec4 color);
	private:
		void SubmitVertice(const Vertex2D& vertice);
		void InitBuffers();
	private:
		VertexArray* m_Vao;
		VertexBuffer* m_Vbo;
		IndexBuffer* m_Ibo;
		Shader* m_FlatShader;
		const unsigned int m_VertexBufferSize = 100000;
		unsigned int m_VerticeAmount;
	public:
		static Renderer2D* s_Renderer;
	};

}
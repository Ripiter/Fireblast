#pragma once
#include "Graphics/Api/RenderCommands.h"
#include "Graphics/Api/RenderAPI.h"
#include "Graphics/Vertice.h"
#include "Utils/FileUtils.h"
#include "Entity/Entity.h"

namespace Fireblast 
{
	class Renderer2D
	{
	private:
		VertexArray* m_Vao;
		VertexBuffer* m_Vbo;
		IndexBuffer* m_Ibo;
		Shader* m_FlatShader;
		const unsigned int m_VertexBufferSize = 100000;
		unsigned int m_VerticeAmount;
		std::vector<Entity*> m_Entities;
	public:
		static std::shared_ptr<Renderer2D> s_Renderer;
	public:
		Renderer2D()
			: m_Vao(NULL), m_Vbo(NULL), m_Ibo(NULL), m_FlatShader(NULL), m_VerticeAmount(0) {}

		void BeginSubmit();
		void EndSubmit();
		void Onstart();
		void OnUpdate();
		void OnDraw();

		void SubmitEntity(Entity* entity);
		
		void SubmitVertice(const Vertex2D& vertice);
	private:
		void InitBuffers();

	};

}
#pragma once
#include "Graphics/Api/RenderCommands.h"
#include "Graphics/Api/RenderAPI.h"
#include "Graphics/Vertice.h"
#include "Utils/FileUtils.h"
#include "Entity/Entity.h"
#include "Core/System.h"

namespace Fireblast 
{
	class Renderer2D : public System
	{
	private:
		VertexArray* m_Vao;
		VertexBuffer* m_Vbo;
		IndexBuffer* m_Ibo;
		Shader* m_FlatShader;
		const unsigned int m_VertexBufferSize = 100000;
		unsigned int m_VerticeAmount;
	public:
		Renderer2D()
			: m_Vao(NULL), m_Vbo(NULL), m_Ibo(NULL), m_FlatShader(NULL), m_VerticeAmount(0) {}

		void BeginSubmit();
		void EndSubmit();

		void SubmitEntity(Entity* entity);
		
		void SubmitVertice(const Vertex2D& vertice);
	private:
		void InitBuffers();

	protected:
		virtual void OnStart() override;

		virtual void OnUpdate() override;

		virtual void OnDraw() override;

	};

}
#include "fbpch.h"
#include "Renderer2D.h"
#include "Entity/Component/Components.h"
#include "Core/SManager.h"

namespace Fireblast 
{
	Vertex2D* m_BufferPointer;
	std::shared_ptr<Renderer2D> Fireblast::Renderer2D::s_Renderer = std::make_shared<Renderer2D>();


	void Fireblast::Renderer2D::InitBuffers()
	{
		m_Vao = RenderAPI::GetApi()->CreateVertexArray();
		m_Vbo = RenderAPI::GetApi()->CreateVertexBuffer(m_VertexBufferSize);
		m_Ibo = RenderAPI::GetApi()->CreateIndexBuffer(m_VertexBufferSize * 6);

		m_Vao->Bind();
		m_Vbo->Bind();

		m_Vbo->SetLayout({
			{0, 3, Fireblast::ShaderType::Float, false},
			{1, 4, Fireblast::ShaderType::Float, false},
			{2, 2, Fireblast::ShaderType::Float, false}
		});
		
		m_Vao->SetVertexBuffer(m_Vbo);
		m_Vao->SetIndexBuffer(m_Ibo);
	}

	void Fireblast::Renderer2D::BeginSubmit()
	{
		m_BufferPointer = (Vertex2D*)m_Vbo->GetPointer();
		m_VerticeAmount = 0;
	}

	void Fireblast::Renderer2D::EndSubmit()
	{
		m_Vbo->ReleasePointer();
	}
	
	void Fireblast::Renderer2D::Start()
	{
		InitBuffers();

		m_FlatShader = Fireblast::RenderAPI::GetApi()->CreateShader
		(
			std::string("C:/repos/Fireblast/src/vFlatShader.txt"),
			std::string("C:/repos/Fireblast/src/fFlatShader.txt")
		);

		FileUtils::FlipImages(true);

	}

	void Fireblast::Renderer2D::Update()
	{
		std::vector<Entity*>& m_Entities = SManager::Get()->GetManager<SceneManager>()->GetActiveScene()->GetEntities();

		for (unsigned int i = 0; i < m_Entities.size(); i++)
		{
			auto* transform = m_Entities[i]->GetComponent<Transform>();

			auto* it = m_Entities[i]->GetComponent<SpriteComponent>();
			if (!it)
				continue;

			glm::mat4 modelMat = transform->GetTransformMatrix();

			m_BufferPointer->Vertice = modelMat * glm::vec4(it->m_Vertices[0].Vertice.x, it->m_Vertices[0].Vertice.y, it->m_Vertices[0].Vertice.z, 1.0f);
			m_BufferPointer->Color = it->m_Vertices[0].Color;
			m_BufferPointer->Uv = it->m_Vertices[0].Uv;
			m_BufferPointer++;

			m_BufferPointer->Vertice = modelMat * glm::vec4(it->m_Vertices[1].Vertice.x, it->m_Vertices[1].Vertice.y, it->m_Vertices[1].Vertice.z, 1.0f);
			m_BufferPointer->Color = it->m_Vertices[1].Color;
			m_BufferPointer->Uv = it->m_Vertices[1].Uv;
			m_BufferPointer++;

			m_BufferPointer->Vertice = modelMat * glm::vec4(it->m_Vertices[2].Vertice.x, it->m_Vertices[2].Vertice.y, it->m_Vertices[2].Vertice.z, 1.0f);
			m_BufferPointer->Color = it->m_Vertices[2].Color;
			m_BufferPointer->Uv = it->m_Vertices[2].Uv;
			m_BufferPointer++;

			m_BufferPointer->Vertice = modelMat * glm::vec4(it->m_Vertices[3].Vertice.x, it->m_Vertices[3].Vertice.y, it->m_Vertices[3].Vertice.z, 1.0f);
			m_BufferPointer->Color = it->m_Vertices[3].Color;
			m_BufferPointer->Uv = it->m_Vertices[3].Uv;
			m_BufferPointer++;

			m_VerticeAmount += 6;

		}
	}


	void Fireblast::Renderer2D::SubmitVertice(const Vertex2D& vertice)
	{
		m_BufferPointer->Vertice = vertice.Vertice;
		m_BufferPointer->Color = vertice.Color;
		m_BufferPointer->Uv = vertice.Uv;
		m_BufferPointer++;
	}

	void Renderer2D::SubmitEntity(Entity* entity)
	{
		//m_Entities.push_back(entity);
	}

	void Fireblast::Renderer2D::Draw()
	{
		RenderAPI::GetApi()->SetBlend(true);

		m_FlatShader->Bind();
		
		m_Ibo->Bind();
		m_Vao->DrawIndicies(Fireblast::RenderPrimitives::Triangles, m_VerticeAmount);
	}
}
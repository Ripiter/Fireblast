#include "fbpch.h"
#include "Renderer2D.h"

namespace Fireblast 
{
	Vertex2D* m_BufferPointer;
	Fireblast::Renderer2D* Fireblast::Renderer2D::s_Renderer = new Fireblast::Renderer2D();

	// TEST
	Fireblast::Texture* text;

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
	
	void Fireblast::Renderer2D::Onstart()
	{
		InitBuffers();

		m_FlatShader = Fireblast::RenderAPI::GetApi()->CreateShader
		(
			std::string("C:/repos/Fireblast/src/vFlatShader.txt"),
			std::string("C:/repos/Fireblast/src/fFlatShader.txt")
		);

		FileUtils::FlipImages(true);

		text = RenderAPI::GetApi()->CreateTexture("C:/Users/eadr/Desktop/Fish.png");
	}

	void Fireblast::Renderer2D::OnUpdate()
	{
		
	}

	void Fireblast::Renderer2D::SubmitQuad(const glm::vec3 centerPos, const glm::vec2 size, const glm::vec4 color)
	{
		Vertex2D _data[4];

		_data[0].Vertice = glm::vec3(centerPos.x - size.x / 2, centerPos.y + size.y / 2, centerPos.z);
		_data[0].Color = color;
		_data[0].Uv = glm::vec2(0, 1);

		_data[1].Vertice = glm::vec3(centerPos.x + size.x / 2, centerPos.y + size.y / 2, centerPos.z);
		_data[1].Color = color;
		_data[1].Uv = glm::vec2(1, 1);

		_data[2].Vertice = glm::vec3(centerPos.x + size.x / 2, centerPos.y - size.y / 2, centerPos.z);
		_data[2].Color = color;
		_data[2].Uv = glm::vec2(1, 0);

		_data[3].Vertice = glm::vec3(centerPos.x - size.x / 2, centerPos.y - size.y / 2, centerPos.z);
		_data[3].Color = color;
		_data[3].Uv = glm::vec2(0, 0);

		SubmitVertice(_data[0]);
		SubmitVertice(_data[1]);
		SubmitVertice(_data[2]);
		SubmitVertice(_data[3]);

		m_VerticeAmount += 6;
	}

	void Fireblast::Renderer2D::SubmitTriangle(const glm::vec3 centerPos, const glm::vec2 size, const glm::vec4 color)
	{
		Vertex2D _data[3];

		_data[0].Vertice = glm::vec3(centerPos.x, centerPos.y + size.y / 2, centerPos.z);
		_data[0].Color = color;
		_data[0].Uv = glm::vec2(0.5f, 1.f);

		_data[1].Vertice = glm::vec3(centerPos.x + size.x / 2, centerPos.y - size.y / 2, centerPos.z);
		_data[1].Color = color;
		_data[1].Uv = glm::vec2(1.f, 0.f);

		_data[2].Vertice = glm::vec3(centerPos.x - size.x / 2, centerPos.y - size.y / 2, centerPos.z);
		_data[2].Color = color;
		_data[2].Uv = glm::vec2(0, 0);

		SubmitVertice(_data[0]);
		SubmitVertice(_data[1]);
		SubmitVertice(_data[2]);

		m_VerticeAmount += 6;
	}

	void Fireblast::Renderer2D::SubmitVertice(const Vertex2D& vertice)
	{
		m_BufferPointer->Vertice = vertice.Vertice;
		m_BufferPointer->Color = vertice.Color;
		m_BufferPointer->Uv = vertice.Uv;
		m_BufferPointer++;
	}

	void Fireblast::Renderer2D::OnDraw()
	{
		RenderAPI::GetApi()->SetBlend(true);

		m_FlatShader->Bind();

		// Texture test
		text->ActivateTexture(0);
		text->Bind();
		
		m_Ibo->Bind();
		m_Vao->DrawIndicies(Fireblast::RenderPrimitives::Triangles, m_VerticeAmount);
	}
}
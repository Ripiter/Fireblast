#include "fbpch.h"
#include "Renderer2D.h"
#include "Entity/Component/Components.h"
#include "Core/SManager.h"

namespace Fireblast 
{
	Vertex2D* m_BufferPointer;

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

	void Renderer2D::OnStart()
	{
		InitBuffers();

		// TODO: Let resourcemanager create the shaders and hold em
		// Then let the renderer2d load default shaders, and let user
		// change em if they want to.
		m_FlatShader = Fireblast::RenderAPI::GetApi()->CreateShader
		(
			std::string("C:/repos/Fireblast/src/vFlatShader.txt"),
			std::string("C:/repos/Fireblast/src/fFlatShader.txt")
		);

		// TODO: Move this to global location where it makes sense to set flag
		FileUtils::FlipImages(true);
	}

	void Renderer2D::OnBeforeUpdate()
	{
		BeginSubmit();
	}

	// TODO: Find a way to submit different primitives from their components
	// And batch them all together.
	// Right now the only component which is being submitted and drawn is
	// The sprite component / quad
	void Renderer2D::OnUpdate()
	{
		std::vector<Entity*>& m_Entities = SManager::Get()->GetManager<SceneManager>()->GetActiveScene()->GetEntities();

		for (unsigned int i = 0; i < m_Entities.size(); i++)
		{
			// Is Entity enabled
			if (!m_Entities[i]->GetEnabled())
				continue;

			// Get transform component
			auto* transform = m_Entities[i]->GetComponent<Transform>();

			// Get sprite component
			auto* it = m_Entities[i]->GetComponent<SpriteComponent>();
			if (!it)
				continue;

			// Check if enabled
			if (!it->GetEnabled())
				continue;

			// Get model matrix
			glm::mat4 modelMat = transform->GetTransformMatrix();

			// Begin submiting data to vbo
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

			// Increase vertices that have to be drawed
			m_VerticeAmount += 6;
		}
	}

	void Renderer2D::OnDraw()
	{
		EndSubmit();

		// Set blend status
		RenderAPI::GetApi()->SetBlend(true);

		m_FlatShader->Bind();

		// Get camera & upload to shader
		OrthographicCamera* _camera = SManager::Get()->GetManager<SceneManager>()->GetActiveScene()->GetOrthographicCamera();
		glm::mat4 cameraModel = _camera->GetViewProjection();
		m_FlatShader->SetMat4("projView", cameraModel);

		// Draw as indicies
		m_Ibo->Bind();
		m_Vao->DrawIndicies(Fireblast::RenderPrimitives::Triangles, m_VerticeAmount);
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
	

}
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
			{2, 2, Fireblast::ShaderType::Float, false},
			{3, 1, Fireblast::ShaderType::Int, false}
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
			if (!IsEntitySubmitable(m_Entities[i]))
				continue;

			SubmitEntity(m_Entities[i]);
		}
	}

	void Renderer2D::OnDraw()
	{
		EndSubmit();

		RenderAPI::GetApi()->SetBlend(true);

		m_FlatShader->Bind();
		UploadUniformsToShader();
		
		m_Ibo->Bind();
		m_Vao->DrawIndicies(Fireblast::RenderPrimitives::Triangles, m_VerticeAmount);
	}

	bool Renderer2D::IsEntitySubmitable(const Entity* entity)
	{
		if (!entity->GetEnabled())						return false;
		if (!entity->GetComponent<Transform>())			return false;
		if (!entity->GetComponent<SpriteComponent>())	return false;

		return true;
	}

	void Renderer2D::SubmitEntity(const Entity* entity)
	{
		const SpriteComponent* spriteComponent	= entity->GetComponent<SpriteComponent>();
		const glm::mat4 modelMat				= entity->GetComponent<Transform>()->GetTransformMatrix();

		const unsigned int _EntityVerticesAmount = 4;
		for (unsigned int i = 0; i < _EntityVerticesAmount; i++)
		{
			m_BufferPointer->Vertice	= modelMat * glm::vec4(spriteComponent->m_Vertices[i].Vertice.x, spriteComponent->m_Vertices[i].Vertice.y, spriteComponent->m_Vertices[i].Vertice.z, 1.0f);
			m_BufferPointer->Color		= spriteComponent->m_Vertices[i].Color;
			m_BufferPointer->Uv			= spriteComponent->m_Vertices[i].Uv;
			m_BufferPointer->TextureID	= 0;
			m_BufferPointer++;
		}

		m_VerticeAmount += 6;
	}

	void Renderer2D::UploadUniformsToShader()
	{
		glm::mat4 _cameraModel = SManager::Get()->GetManager<SceneManager>()->GetActiveScene()->GetOrthographicCamera()->GetViewProjection();
		m_FlatShader->SetMat4("projView", _cameraModel);
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
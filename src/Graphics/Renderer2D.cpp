#include "fbpch.h"
#include "Renderer2D.h"
#include "Entity/Component/Components.h"
#include "Core/SManager.h"
#include "Utils/Performance.h"

#include <unordered_map>

namespace Fireblast 
{
	Vertex2D* m_BufferPointer;
	std::unordered_map<std::string, float> textureBatch;

	void Fireblast::Renderer2D::InitBuffers()
	{
		FB_PERFORMANCE_PROFILE();

		m_Vao = RenderAPI::GetApi()->CreateVertexArray();
		m_Vbo = RenderAPI::GetApi()->CreateVertexBuffer(m_VertexBufferSize);
		m_Ibo = RenderAPI::GetApi()->CreateIndexBuffer(m_VertexBufferSize * 6);

		m_Vao->Bind();
		m_Vbo->Bind();

		m_Vbo->SetLayout({
			{0, 3, Fireblast::ShaderType::Float, false},
			{1, 4, Fireblast::ShaderType::Float, false},
			{2, 2, Fireblast::ShaderType::Float, false},
			{3, 1, Fireblast::ShaderType::Float, false}
		});
		
		m_Vao->SetVertexBuffer(m_Vbo);
		m_Vao->SetIndexBuffer(m_Ibo);
	}

	void Renderer2D::OnStart()
	{
		FB_PERFORMANCE_PROFILE();

		InitBuffers();
		m_FlatShader = SManager::Get()->GetManager<ResourceManager>()->GetShader("Default2DShader");

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
		FB_PERFORMANCE_PROFILE();

		textureBatch.clear();
		int _CurrentTextureSlotIterator = 0;
		std::vector<Entity*>& m_Entities = SManager::Get()->GetManager<SceneManager>()->GetActiveScene()->GetEntities();
		for (unsigned int i = 0; i < m_Entities.size(); i++)
		{
			if (!IsEntitySubmitable(m_Entities[i]))
				continue;

			SubmitEntity(m_Entities[i], &_CurrentTextureSlotIterator);
		}
	}

	void Renderer2D::OnDraw()
	{
		FB_PERFORMANCE_PROFILE();

		EndSubmit();

		RenderAPI::GetApi()->SetBlend(true);

		m_FlatShader->Bind();
		BatchTexturesForSlots();
		UploadUniformsToShader();
		
		m_Ibo->Bind();
		m_Vao->DrawIndicies(Fireblast::RenderPrimitives::Triangles, m_VerticeAmount);

	}

	bool Renderer2D::IsEntitySubmitable(const Entity* entity)
	{
		FB_PERFORMANCE_PROFILE();

		if (!entity->GetEnabled())						return false;
		if (!entity->GetComponent<Transform>())			return false;
		if (!entity->GetComponent<SpriteComponent>())	return false;

		return true;
	}

	void Renderer2D::SubmitEntity(const Entity* entity, int* textureSlotIterator)
	{
		FB_PERFORMANCE_PROFILE();

		const SpriteComponent* spriteComponent	= entity->GetComponent<SpriteComponent>();
		const glm::mat4 modelMat				= entity->GetComponent<Transform>()->GetTransformMatrix();

		// HACK: maybe move this into it's own function for texture batching
		float _TextureSlot = 0;
		if (textureBatch.insert({ spriteComponent->GetTextureName(), *textureSlotIterator }).second)
		{
			_TextureSlot = *textureSlotIterator;
			(*textureSlotIterator)++;
		}
		else
			_TextureSlot = textureBatch.find(spriteComponent->GetTextureName())->second;

		const Vertex2D* vertices					= spriteComponent->GetVertices();
		const unsigned int _EntityVerticesAmount	= 4;
		for (unsigned int i = 0; i < _EntityVerticesAmount; i++)
		{
			m_BufferPointer->Vertice	= modelMat * glm::vec4(vertices[i].Vertice.x, vertices[i].Vertice.y, vertices[i].Vertice.z, 1.0f);
			m_BufferPointer->Color		= vertices[i].Color;
			m_BufferPointer->Uv			= vertices[i].Uv;
			m_BufferPointer->TextureID	= _TextureSlot;
			m_BufferPointer++;
		}

		m_VerticeAmount += 6;

	}

	void Renderer2D::BatchTexturesForSlots()
	{
		FB_PERFORMANCE_PROFILE();

		for ( auto& it : textureBatch )
		{
			Texture* _currentTexture = SManager::Get()->GetManager<ResourceManager>()->GetTexture(it.first);
			_currentTexture->ActivateTexture(it.second);
			m_FlatShader->SetInt(std::string("textures[") + std::to_string((int)it.second) + "]", it.second);
		}
	}

	void Renderer2D::UploadUniformsToShader()
	{
		FB_PERFORMANCE_PROFILE();

		glm::mat4 _cameraModel = SManager::Get()->GetManager<SceneManager>()->GetActiveScene()->GetOrthographicCamera()->GetViewProjection();
		m_FlatShader->SetMat4("projView", _cameraModel);
	}

	void Fireblast::Renderer2D::BeginSubmit()
	{
		FB_PERFORMANCE_PROFILE();

		m_BufferPointer = (Vertex2D*)m_Vbo->GetPointer();
		m_VerticeAmount = 0;
	}

	void Fireblast::Renderer2D::EndSubmit()
	{
		FB_PERFORMANCE_PROFILE();

		m_Vbo->ReleasePointer();
	}
}
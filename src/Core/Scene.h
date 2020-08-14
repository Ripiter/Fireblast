#pragma once
#include "Entity/Entity.h"
#include "OrthographicCamera.h"

#include <vector>
#include <memory>

namespace Fireblast
{
	class Scene
	{
		friend class SceneManager;
		friend class Application;
	private:
		std::vector<Entity*> m_Entities;
		OrthographicCamera* m_OrthoCamera;
	public:
		Scene();
		virtual ~Scene();
	public:
		std::vector<Entity*>& GetEntities() { return m_Entities; }
		OrthographicCamera* GetOrthographicCamera() const { return m_OrthoCamera; }

		void DestroyEntity(Entity* entity);
	protected:
		void SpawnEntity(Entity* entity);
		void SpawnEntity(Entity* entity, glm::vec3 pos);

		inline void SetOrthographicCamera(OrthographicCamera* camera) { m_OrthoCamera = camera; }
	protected:
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
	private:
		void Start();
		void Update();
	};
}
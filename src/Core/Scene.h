#pragma once
#include "Entity/Entity.h"
#include "glm/glm.hpp"

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

	public:
		std::vector<Entity*>& GetEntities() { return m_Entities; }
	public:
		Scene();
		virtual ~Scene();
	protected:
		void SpawnEntity(Entity* entity);
		void SpawnEntity(Entity* entity, glm::vec3 pos);
	protected:
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;

	private:
		void Start();
		void Update();
	};
}
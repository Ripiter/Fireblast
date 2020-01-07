#pragma once
#include "Entity/Entity.h"
#include "glm/glm.hpp"

#include <vector>
#include <memory>

namespace Fireblast
{

	class Scene
	{
		friend class Renderer2D;
		friend class Application;

	private:
		std::vector<Entity*> m_Entities;
		static std::shared_ptr<Scene> s_currentScene;
	public:
		Scene();
		virtual ~Scene();

		static void LoadScene(std::shared_ptr<Scene> scene);
		inline static std::shared_ptr<Scene>& GetCurrentScene() { return s_currentScene; }
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
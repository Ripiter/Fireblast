#include "fbpch.h"
#include "Scene.h"
#include <Entity\Component\Transform.h>

namespace Fireblast
{

	Scene::Scene()
		: m_Entities() {}

	Scene::~Scene()
	{
	}


	void Scene::SpawnEntity(Entity* entity)
	{
		m_Entities.push_back(entity);
		entity->Start();
	}

	void Scene::SpawnEntity(Entity* entity, glm::vec3 pos)
	{
		SpawnEntity(entity);
		entity->GetComponent<Transform>()->SetPosition(pos);
	}

	void Scene::Start()
	{
		OnStart();
	}

	void Scene::Update()
	{
		OnUpdate();

		for (unsigned int i = 0; i < m_Entities.size(); i++)
		{
			m_Entities[i]->Update();
		}
	}

}
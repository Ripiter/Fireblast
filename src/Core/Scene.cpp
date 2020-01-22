#include "fbpch.h"
#include "Scene.h"
#include "Entity\Component\Transform.h"
#include "Utils/Performance.h"

namespace Fireblast
{

	Scene::Scene()
		: m_Entities(), m_OrthoCamera(new OrthographicCamera(0.f, 0.f, 16.f, 16.f))
	{
	}

	Scene::~Scene()
	{
		delete m_OrthoCamera;
		for (auto p : m_Entities)
		{
			delete p;
		}
		m_Entities.clear();
	}


	void Scene::SpawnEntity(Entity* entity)
	{
		FB_PERFORMANCE_PROFILE();

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
		FB_PERFORMANCE_PROFILE();

		OnStart();

	}

	void Scene::Update()
	{
		FB_PERFORMANCE_PROFILE();

		OnUpdate();

		for (unsigned int i = 0; i < m_Entities.size(); i++)
		{
			m_Entities[i]->Update();
		}

	}

}
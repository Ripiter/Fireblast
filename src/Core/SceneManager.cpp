#include "fbpch.h"
#include "SceneManager.h"
#include "Application/Log.h"

#include "Utils/Performance.h"

namespace Fireblast
{
	SceneManager::SceneManager()
		: m_ActiveScene(nullptr), m_Scenes() {}

	SceneManager::~SceneManager()
	{
		for (auto element : m_Scenes)
		{
			delete element.second;
		}
	}

	void SceneManager::CreateScene(const std::string& name, Scene* scene)
	{
		FB_PERFORMANCE_START_PROFILEFUNCTION();

		if (!m_Scenes.insert({ name, scene }).second)
			FB_CORE_WARN("{0} Already exists", name);

		FB_PERFORMANCE_END_PROFILEFUNCTION();
	}

	void SceneManager::LoadScene(const std::string& name)
	{
		FB_PERFORMANCE_START_PROFILEFUNCTION();

		auto& _pair = m_Scenes.find(name);
		if (!_pair->second)
		{
			FB_CORE_WARN("Couldn't load scene named {0} do not exists", name);
			return;
		}

		m_ActiveScene = _pair->second;
		m_ActiveScene->Start();
		FB_CORE_INFO("Loaded Scene {0}", name);

		FB_PERFORMANCE_END_PROFILEFUNCTION();
	}

	void SceneManager::OnStart()
	{
	}

	void SceneManager::OnUpdate()
	{
		FB_PERFORMANCE_END_PROFILEFUNCTION();

		if (!m_ActiveScene)
			return;

		m_ActiveScene->Update();

		FB_PERFORMANCE_END_PROFILEFUNCTION();
	}


	void SceneManager::OnDraw()
	{
	}
}
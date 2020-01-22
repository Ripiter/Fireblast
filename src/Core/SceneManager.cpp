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

		m_Scenes.clear();
	}

	void SceneManager::CreateScene(const std::string& name, Scene* scene)
	{
		FB_PERFORMANCE_PROFILE();

		if (!m_Scenes.insert({ name, scene }).second)
			FB_CORE_WARN("{0} Already exists", name);

	}

	void SceneManager::LoadScene(const std::string& name)
	{
		FB_PERFORMANCE_PROFILE();

		auto& _pair = m_Scenes.find(name);
		if (!_pair->second)
		{
			FB_CORE_WARN("Couldn't load scene named {0} do not exists", name);
			return;
		}

		m_ActiveScene = _pair->second;
		m_ActiveScene->Start();
		FB_CORE_INFO("Loaded Scene {0}", name);

	}

	void SceneManager::OnStart()
	{
	}

	void SceneManager::OnUpdate()
	{
		FB_PERFORMANCE_PROFILE();

		if (!m_ActiveScene)
			return;

		m_ActiveScene->Update();

	}


	void SceneManager::OnDraw()
	{
	}
}
#include "fbpch.h"
#include "SceneManager.h"
#include "Application/Log.h"

namespace Fireblast
{

	void SceneManager::CreateScene(const std::string& name, Scene* scene)
	{
		if (!m_Scenes.insert({ name, scene }).second)
			FB_CORE_WARN("{0} Already exists", name);
	}

	void SceneManager::LoadScene(const std::string& name)
	{
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
		if (!m_ActiveScene)
			return;

		m_ActiveScene->Update();
	}


	void SceneManager::OnDraw()
	{
	}
}
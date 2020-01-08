#pragma once
#include "Core/Scene.h"
#include <vector>
#include <unordered_map>

namespace Fireblast
{
	class SceneManager
	{
	private:
		static std::shared_ptr<SceneManager> s_Instance;
	public:
		static std::shared_ptr<SceneManager>& Get() { return s_Instance; };
	private:
		Scene* m_ActiveScene;
		std::unordered_map<std::string, Scene*> m_Scenes;
	public:
		void CreateScene(const std::string& name, Scene* scene);
		void LoadScene(const std::string& name);
	public:
		Scene* GetActiveScene() const { return m_ActiveScene; }
	};
}
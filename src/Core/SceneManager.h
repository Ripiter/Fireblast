#pragma once
#include "Core/Scene.h"
#include "Core/Manager.h"
#include <vector>
#include <unordered_map>

namespace Fireblast
{
	class SceneManager : public Manager
	{
	private:
		Scene* m_ActiveScene;
		std::unordered_map<std::string, Scene*> m_Scenes;
	public:
		SceneManager();
		~SceneManager();

		void CreateScene(const std::string& name, Scene* scene);
		void LoadScene(const std::string& name);
	public:
		Scene* GetActiveScene() const { return m_ActiveScene; }

		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnDraw() override;
	};
}
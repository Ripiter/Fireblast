#pragma once
#include "Core/Manager.h"
#include "Core/SceneManager.h"
#include "Core/SystemManager.h"
#include "Core/ResourceManager.h"
#include <vector>
#include <memory>

namespace Fireblast
{
	class SManager
	{
	friend class Application;

	private:
		std::vector<Manager*> m_Managers;
		static std::shared_ptr<SManager> s_Instance;
	public:
		static std::shared_ptr<SManager>& Get() { return s_Instance; }
	public:
		void AddManager(Manager* manager)
		{
			m_Managers.push_back(manager);
		}

		template<typename T>
		T* GetManager() 
		{
			return (T*)GetManagerInternal<T>();
		}

		template<typename T>
		const T* GetManager() const
		{
			return GetManagerInternal<T>();
		}

	private:
		// TODO: make it so it can detect sub classes or super classes
		template<typename T>
		const T* GetManagerInternal() const
		{
			for (auto* it : m_Managers)
			{
				if (typeid(*it).name() == typeid(T).name())
					return (T*)it;
			}

			return nullptr;
		}

		inline void Start() 
		{
			// Add systems
			AddManager(new ResourceManager());
			AddManager(new SceneManager());
			AddManager(new SystemManager());

			for (unsigned int i = 0; i < m_Managers.size(); i++)
			{
				m_Managers[i]->Start();
			}
		};

		inline void BeforeUpdate()
		{
			for (unsigned int i = 0; i < m_Managers.size(); i++)
			{
				m_Managers[i]->BeforeUpdate();
			}
		}

		inline void Update() 
		{
			for (unsigned int i = 0; i < m_Managers.size(); i++)
			{
				m_Managers[i]->Update();
			}
		};

		inline void Draw() 
		{
			for (unsigned int i = 0; i < m_Managers.size(); i++)
			{
				m_Managers[i]->Draw();
			}
		};
	};
}
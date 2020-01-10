#pragma once
#include "Graphics/Renderer2D.h"
#include "Core/Manager.h"
#include "Core/System.h"
#include <vector>

namespace Fireblast
{
	class SystemManager : public Manager
	{
	private:
		std::vector<System*> m_Systems;

	public:
		inline void Add(System* system) { m_Systems.push_back(system); };

		template<typename T>
		inline const T* GetSystem() const { return GetInternalSystem<T>(); }

		template<typename T>
		inline T* GetSystem() { return (T*)GetInternalSystem<T>(); }
	private:	
		template<typename T>
		inline const T* GetInternalSystem() const
		{
				for (auto* it : m_Systems)
				{
					if (typeid(*it).name() == typeid(T).name())
						return (T*)it;
				}

				return nullptr;
		}
	protected:
		inline virtual void OnStart() override 
		{
			Add(new Renderer2D());

			for (unsigned int i = 0; i < m_Systems.size(); i++)
			{
				m_Systems[i]->Start();
			}
		};

		inline virtual void OnUpdate() override 
		{
			for (unsigned int i = 0; i < m_Systems.size(); i++)
			{
				m_Systems[i]->Update();
			}
		};

		inline virtual void OnDraw() override 
		{
			for (unsigned int i = 0; i < m_Systems.size(); i++)
			{
				m_Systems[i]->Draw();
			}
		};
	};
}
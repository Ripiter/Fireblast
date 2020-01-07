#pragma once
#include "Component/Component.h"

#include <vector>

namespace Fireblast
{
	class Entity
	{
	private:
		unsigned int m_Id;
		std::vector<Component*> m_Components;
	protected:
		virtual void Start() = 0;
		virtual void Update() = 0;
	public:
		Entity();
		virtual ~Entity();
	public:
		void AddComponent(Component* component);
		
		template<typename T>
		T* GetComponent() 
		{
			return (T*)GetComponentInternal<T>();
		}

		template<typename T>
		const T* GetComponent() const
		{
			return GetComponentInternal<T>();
		}

		std::vector<Component*>::iterator begin() { return m_Components.begin(); }
		std::vector<Component*>::iterator end() { return m_Components.end(); }
		std::vector<Component*>::const_iterator begin() const { return m_Components.begin(); }
		std::vector<Component*>::const_iterator end() const { return m_Components.end(); }

	private:
		template<typename T>
		const T* GetComponentInternal() const
		{
			for(auto* it : m_Components)
			{
				if (typeid(*it).name() == typeid(T).name())
					return (T*)it;
			}

			return nullptr;
		}
	};
}
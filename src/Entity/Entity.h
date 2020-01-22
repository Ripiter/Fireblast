#pragma once
#include "Component/Component.h"

#include <vector>

namespace Fireblast
{
	class Entity
	{
		friend class Scene;
	private:
		unsigned int m_Id;
		bool m_Enabled;
		std::vector<Component*> m_Components;
	public:
		Entity();
		virtual ~Entity();
	private:
		void Start();
		void Update();
	protected:
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
	public:
		void AddComponent(Component* component);

		inline const bool GetEnabled() const { return m_Enabled; }
		inline void SetEnabled(const bool enabled) { m_Enabled = enabled; }
		
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
		// TODO: The current function can only detect the current class
		// and doesn't take into account if the class has inheritance.
		// Maybe create it so that it can look past that with special
		// parameters
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
#include "fbpch.h"
#include "Component/Transform.h"
#include "Entity.h"

namespace Fireblast
{
	Entity::Entity()
		: m_Id(0), m_Components(), m_Enabled(true)
	{
		AddComponent(new Transform());
	}

	void Entity::AddComponent(Component* component)
	{
		m_Components.push_back(component);
	}

	void Entity::Start()
	{
		OnStart();
	}

	void Entity::Update()
	{
		OnUpdate();
	}

	Entity::~Entity()
	{
		for (auto it : m_Components)
		{
			delete it;
		}
		m_Components.clear();
	}


}
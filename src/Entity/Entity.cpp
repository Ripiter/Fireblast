#include "fbpch.h"
#include "Component/Transform.h"
#include "Entity.h"
#include "Graphics/Renderer2D.h" // TODO let scene handle entities

namespace Fireblast
{
	Entity::Entity()
		: m_Id(0), m_Components()
	{
		AddComponent(new Transform());
		Renderer2D::s_Renderer->SubmitEntity(this);
	}

	void Entity::AddComponent(Component* component)
	{
		m_Components.push_back(component);
	}

	Entity::~Entity()
	{
		// iterate components and delete components
		for (auto* it : m_Components)
		{
			delete it;
		}
	}


}
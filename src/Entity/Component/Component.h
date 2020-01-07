#pragma once

namespace Fireblast
{
	class Entity;

	class Component
	{
	protected:
		Entity* m_Entity;
	public:
		virtual Entity* GetEntity() { return m_Entity; }
	};
}
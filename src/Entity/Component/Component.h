#pragma once

namespace Fireblast
{
	class Entity;

	// TODO: M_Entity is never initialised
	// to the correct value
	// should probably link it when a component
	// is appended to an entity
	class Component
	{
	private:
		bool m_Enabled;
	protected:
		Entity* m_Entity;
	public:
		Component() : m_Enabled(true), m_Entity(nullptr) {}
		virtual ~Component() {}
	public:
		inline const bool GetEnabled() const { return m_Enabled; }
		inline void SetEnabled(const bool enabled) { m_Enabled = enabled; }

		virtual Entity* GetEntity() { return m_Entity; }
	};
}
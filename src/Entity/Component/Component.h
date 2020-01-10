#pragma once

namespace Fireblast
{
	class Entity;

	class Component
	{
	private:
		bool m_Enabled;
	protected:
		Entity* m_Entity;
	public:
		inline const bool GetEnabled() const { return m_Enabled; }
		inline void SetEnabled(const bool enabled) { m_Enabled = enabled; }

		virtual Entity* GetEntity() { return m_Entity; }
	};
}
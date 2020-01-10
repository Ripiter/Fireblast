#pragma once

namespace Fireblast
{
	class Manager
	{
		friend class SManager;

	private:
		inline void Start() { OnStart(); }
		inline void BeforeUpdate() { OnBeforeUpdate(); }
		inline void Update() { OnUpdate(); }
		inline void Draw() { OnDraw(); }
	protected:
		virtual void OnStart() = 0;
		virtual void OnBeforeUpdate() {};
		virtual void OnUpdate() = 0;
		virtual void OnDraw() = 0;
	};
}
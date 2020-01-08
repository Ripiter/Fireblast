#pragma once
namespace Fireblast
{
	class System
	{
		friend class SystemManager;
	private:
		inline void Start() { OnStart(); };
		inline void Update() { OnUpdate(); };
		inline void Draw() { OnDraw(); };

	protected:
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDraw() = 0;
	};
}
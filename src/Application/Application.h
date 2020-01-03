#pragma once
#include "WndWindow.h"
#include "Application/Input.h"
#include "Application/Log.h"
#include "Application/Time.h"

namespace Fireblast {
	class Application
	{
	private:
		bool m_IsRunning;
		WndWindow* m_WindowInstance;

	private:
		void OnApplicationEvent(Event& event);
	public:
		Application();
		virtual ~Application();
		void Run();
	public:
		virtual void OnStart() = 0;
		virtual void OnAfterStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDraw() = 0;
	};
};


